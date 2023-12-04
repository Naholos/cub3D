/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoteo-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 11:59:52 by aoteo-be          #+#    #+#             */
/*   Updated: 2022/01/20 11:54:52 by aoteo-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

// Función para obtener la imagen de las texturas
void	get_image(t_mlx *mlx, char symbol)
{
	int	dim;

	dim = TEXT_DIM;
	if (symbol == 'N')
		mlx->img = mlx_xpm_file_to_image(mlx->mlx, NORTH, &dim, &dim);
	if (symbol == 'S')
		mlx->img = mlx_xpm_file_to_image(mlx->mlx, SOUTH, &dim, &dim);
	if (symbol == 'E')
		mlx->img = mlx_xpm_file_to_image(mlx->mlx, EAST, &dim, &dim);
	if (symbol == 'W')
		mlx->img = mlx_xpm_file_to_image(mlx->mlx, WEST, &dim, &dim);
}

// Función para determinar la dirección a la que mira el jugador según el valor
// de la variable que marca suposición inicial
t_coord	get_dir(char dir)
{
	t_coord	coord;

	coord.x = 0;
	coord.y = 0;
	if (dir == 'N')
		coord.y = -1;
	if (dir == 'S')
		coord.y = 1;
	if (dir == 'W')
		coord.x = -1;
	if (dir == 'E')
		coord.x = 1;
	return (coord);
}

// Función que recupera la posición inicial de un jugador
t_player	*locate_player(t_map *m)
{
	int			x;
	int			y;
	t_coord		coord;
	t_player	*p;

	p = malloc(sizeof(t_player));
	if (p == NULL)
		map_errors(0, "");
	y = -1;
	while (m->map[++y])
	{
		x = -1;
		while (m->map[y][++x])
		{
			if (check_chars(m, m->map[y][x], y, x))
			{
				coord = get_dir(m->map[y][x]);
				p->dirx = coord.x;
				p->diry = coord.y;
				p->x = x;
				p->y = y;
				return (p);
			}
		}
	}
	exit(EXIT_FAILURE);
}

// Función que inicializa el rayo
void	init_ray(t_ray *ray, t_player *player)
{
	ray->time = 0;
	ray->pos.hit = 0;
	ray->old_time = 0;
	ray->pos.x = player->x;
	ray->pos.y = player->y;
	ray->pos.dirx = player->dirx;
	ray->pos.diry = player->diry;
	ray->plane.x = 0;
	ray->plane.y = FOV;
}

// Función para realizar el casting de rayos
void	cast_rays(t_cub *cub)
{
	int		color;
	int		h;
	int		w;
	int		mapX;
	int		mapY;
	int		side;
	int 	x;
	int 	y;
	int		texNum;
	int		texX;
	int		texY;
	double	frametime;
	double	movespeed;
	double	rotspeed;
	double	step;
	double	texPos;
	double	olddirx;
	double	oldplanex;
	double	oldtime;
	double	time;

	w = WIN_WIDTH;
	h = WIN_HEIGHT;
	// Itera sobre los píxeles de la ventana
	x = -1;
	while (++x < w)
	{
		// Cálculos relacionados con la dirección y posición del rayo
		cub->ray->camerax = 2 * x / (double)w - 1;
		cub->ray->pos.dirx = cub->map->player.dirx + cub->ray->plane.x * cub->ray->camerax;
		cub->ray->pos.diry = cub->map->player.diry + cub->ray->plane.y * cub->ray->camerax;
		// Inicializa variables de posición del mapa
		//mapX = (int)cub->map->player.x;
		//mapY = (int)cub->map->player.y;
		mapX = (int)cub->ray->pos.x;
		mapY = (int)cub->ray->pos.y;
		// Inicializa variables de longitud del rayo
		cub->ray->sidedist.x = 0;
		cub->ray->sidedist.y = 0;
		// Inicializa variables de longitud del rayo desde un lado a otro
		if (cub->ray->pos.dirx == 0)
			cub->ray->deltadist.x = INFINITE;
		else
			cub->ray->deltadist.x = fabs(1 / cub->ray->pos.dirx);
		if (cub->ray->pos.diry == 0)
			cub->ray->deltadist.y = INFINITE;
		else
			cub->ray->deltadist.y = fabs(1 / cub->ray->pos.diry);
		// Inicializa variables de distancia de la pared perpendicular
		cub->ray->perpwalldist = 0;
		// Inicializa variables de dirección para el paso en el mapa
		cub->ray->pos.step.x = 0;
		cub->ray->pos.step.y = 0;
		// Inicializa variables de impacto
		cub->ray->pos.hit = 0;
		side = 0;
		// Calcula paso y distancia inicial
		if (cub->ray->pos.dirx < 0)
		{
			cub->ray->pos.step.x = -1;
			cub->ray->sidedist.x = (cub->map->player.x - mapX) * cub->ray->deltadist.x;
		}
		else
		{
			cub->ray->pos.step.x = 1;
			cub->ray->sidedist.x = (mapX + 1.0 - cub->map->player.x) * cub->ray->deltadist.x;
		}
		if (cub->ray->pos.diry < 0)
		{
			cub->ray->pos.step.y = -1;
			cub->ray->sidedist.y = (cub->map->player.y - mapY) * cub->ray->deltadist.y;
		}
		else
		{
			cub->ray->pos.step.y = 1;
			cub->ray->sidedist.y = (mapY + 1.0 - cub->map->player.y) * cub->ray->deltadist.y;
		}
		// Realiza el algoritmo DDA
		while (cub->ray->pos.hit == 0)
		{
			if (cub->ray->sidedist.x < cub->ray->sidedist.y)
			{
				cub->ray->sidedist.x += cub->ray->deltadist.x;
				mapX += cub->ray->pos.step.x;
				side = 0;
			}
			else
			{
				cub->ray->sidedist.y += cub->ray->deltadist.y;
				mapY += cub->ray->pos.step.y;
				side = 1;
			}
			printf("%d, %d\n", mapX, mapY);
			if (cub->map->map[mapY][mapX] == '1')
				cub->ray->pos.hit = 1;
		}
		// Aquí es donde seleccionas la textura
		t_textures	*current_tex;
		if (side == 0)
		{
			if (cub->ray->pos.dirx > 0)
				current_tex = &cub->e_img;
			else
				current_tex = &cub->w_img;
		}
		else
		{
			if (cub->ray->pos.diry > 0)
				current_tex = &cub->n_img;
			else
				current_tex = &cub->s_img;
		}
		// Calcula distancia del rayo perpendicular
		if (side == 0)
			cub->ray->perpwalldist = (mapX - cub->map->player.x + (1.0 - cub->ray->pos.step.x) / 2.0) / cub->ray->pos.dirx;
		else
			cub->ray->perpwalldist = (mapY - cub->map->player.y + (1.0 - cub->ray->pos.step.y) / 2.0) / cub->ray->pos.diry;
		// Calcula la altura de la línea a dibujar en la pantalla
		cub->ray->line_height = (int)(h / cub->ray->perpwalldist);
		// Calcula los píxeles a dibujar en la línea actual
		cub->ray->draw_start = -cub->ray->line_height / 2 + h / 2;
		if (cub->ray->draw_start < 0)
			cub->ray->draw_start = 0;
		cub->ray->draw_end = cub->ray->line_height / 2 + h / 2;
		if (cub->ray->draw_end >= h)
			cub->ray->draw_end = h - 1;
		// Calcula el número de textura
		texNum = cub->map->map[mapY][mapX] - 1;
		// Calcula la posición exacta de la pared
		if (side == 0)
			cub->ray->wallx = cub->map->player.y + cub->ray->perpwalldist * cub->ray->pos.diry;
		else
			cub->ray->wallx = cub->map->player.x + cub->ray->perpwalldist * cub->ray->pos.dirx;
		cub->ray->wallx -= floor(cub->ray->wallx);
		// Calcula la coordenada x en la textura
		texX = (int)(cub->ray->wallx * (double)current_tex->width);
		if (side == 0 && cub->ray->pos.dirx > 0)
			texX = current_tex->width - texX - 1;
		if (side == 1 && cub->ray->pos.diry < 0)
			texX = current_tex->width - texX - 1;
		// Calcula la cantidad de incremento de la coordenada de la textura por píxel de pantalla
		step = 1.0 * current_tex->height / cub->ray->line_height;
		// Calcula la posición de la textura inicial
		texPos = (cub->ray->draw_start - h / 2 + cub->ray->line_height / 2) * step;
		// Dibuja los píxeles en la línea actual
		y = cub->ray->draw_start - 1;
		while (++y < cub->ray->draw_end)
		{
			texY = (int)texPos & (current_tex->height - 1);
			texPos += step;
			color = get_pixel_color(cub, current_tex, texX, texY);
			if (side == 1)
				color = (color >> 1) & 8355711;
			put_pixel(cub, x, y, color);
		}
	}
/*	drawBuffer(buffer[0]);
	y = -1;
	while (++y < h)
	{
		x = -1;
		while (++x < w)
			buffer[y][x] = 0;
	}
	//timing for input and FPS counter
	oldtime = time;
	time = getTicks();
	frametime = (time - oldtime) / 1000.0; //frametime is the time this frame has taken, in seconds
	redraw();
	//speed modifiers
	movespeed = frametime * 3.0; //the constant value is in squares/second
	rotspeed = frametime * 2.0; //the constant value is in radians/second
	readKeys();
	//move forward if no wall in front of you
	if (keyDown(SDLK_UP))
	{
		if (cub->map->map[(int)(cub->ray->pos.x + cub->ray->pos.dirx * movespeed)][(int)(cub->ray->pos.y)] == 0)
			cub->ray->pos.x += cub->ray->pos.dirx * movespeed;
		if (cub->map->map[(int)(cub->ray->pos.x)][(int)(cub->ray->pos.y + cub->ray->pos.diry * movespeed)] == 0)
			cub->ray->pos.y += cub->ray->pos.diry * movespeed;
	}
	//move backwards if no wall behind you
	if (keyDown(SDLK_DOWN))
	{
		if (cub->map->map[(int)(cub->ray->pos.x - cub->ray->pos.dirx * movespeed)][(int)(cub->ray->pos.y)] == 0)
			cub->ray->pos.x -= cub->ray->pos.dirx * movespeed;
		if (cub->map->map[(int)(cub->ray->pos.x)][(int)(cub->ray->pos.y - cub->ray->pos.diry * movespeed)] == 0)
			cub->ray->pos.y -= cub->ray->pos.diry * movespeed;
	}
	//rotate to the right
	if (keyDown(SDLK_RIGHT))
	{
		//both camera direction and camera plane must be rotated
		olddirx = cub->ray->pos.dirx;
		cub->ray->pos.dirx = cub->ray->pos.dirx * cos(-rotspeed) - cub->ray->pos.diry * sin(-rotspeed);
		cub->ray->pos.diry = olddirx * sin(-rotspeed) + cub->ray->pos.diry * cos(-rotspeed);
		oldplanex = cub->ray->plane.x;
		cub->ray->plane.x = cub->ray->plane.x * cos(-rotspeed) - cub->ray->plane.x * sin(-rotspeed);
		cub->ray->plane.y = oldplanex * sin(-rotspeed) + cub->ray->plane.y * cos(-rotspeed);
	}
	//rotate to the left
	if (keyDown(SDLK_LEFT))
	{
	//both camera direction and camera plane must be rotated
	olddirx = cub->ray->pos.dirx;
	cub->ray->pos.dirx = cub->ray->pos.dirx * cos(rotspeed) - cub->ray->pos.diry * sin(rotspeed);
	cub->ray->pos.diry = olddirx * sin(rotspeed) + cub->ray->pos.diry * cos(rotspeed);
	oldplanex = cub->ray->plane.x;
	cub->ray->plane.x = cub->ray->plane.x * cos(rotspeed) - cub->ray->plane.y * sin(rotspeed);
	cub->ray->plane.y = oldplanex * sin(rotspeed) + cub->ray->plane.y * cos(rotspeed);
	}*/
}
