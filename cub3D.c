/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 23:56:12 by esamad-j          #+#    #+#             */
/*   Updated: 2023/12/01 04:24:46 by esamad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

void	printdoublepointer(char **matrix) //NO BORRAR hasta el final
{
	while (*matrix != NULL && **matrix != '\0')
	{
		printf("%s\n", *matrix);
		matrix++;
	}
}

// Función que verifica si la extensión del archivo es .cub
static int	check_cub(char *argv)
{
	int	n;

	n = (int)ft_strlen(argv);
	if (argv[n - 1] != 'b')
		return (-1);
	if (argv[n - 2] != 'u')
		return (-1);
	if (argv[n - 3] != 'c')
		return (-1);
	if (argv[n - 4] != '.')
		return (-1);
	return (0);
}

// Función que verifica la entrada y muestra mensajes de error en caso necesario
static void	check_input(int parameters_number, char **argv)
{
	if (parameters_number != 2)
	{
		printf("%s%s\n", ERROR, "Usage: cub3D map file name, ");
		if (parameters_number < 2)
			printf("No map file provided.\n");
		else
			printf("Only one parameter allowed.\n");
		exit (EXIT_FAILURE);
	}
	else if (check_cub(argv[1]) == -1)
	{
		printf("%s%s\n", ERROR, "Map extension must be .cub\n");
		exit(EXIT_FAILURE);
	}
}

// Función que verifica si algún parámetro del mapa no está configurado
void	check_no_parameter(t_map *map)
{
	if (map->no == NULL)
		map_errors(2, "NO");
	if (map->so == NULL)
		map_errors(2, "SO");
	if (map->ea == NULL)
		map_errors(2, "EA");
	if (map->we == NULL)
		map_errors(2, "WE");
	if (map->f == NULL)
		map_errors(2, "F");
	if (map->c == NULL)
		map_errors(2, "C");
}

// Función que crea una estructura para almacenar el mapa
t_map	*create_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (map == NULL)
		map_errors(0, "");
	map->no = NULL;
	map->so = NULL;
	map->ea = NULL;
	map->we = NULL;
	map->f = NULL;
	map->c = NULL;
	map->map = NULL;
	map->player.x = 0;
	map->player.y = 0;
	return (map);
}

 //pulsar sobre la "x" y cerrar juego.
int	exit_game(t_mlx *graphics)
{
	mlx_clear_window(graphics->mlx, graphics->win);
	mlx_destroy_window(graphics->mlx, graphics->win);
	exit(0);
}
//cargar en memoria las texturas
void	create_textures(t_cub *cub)
{
	cub->n_img.img = mlx_xpm_file_to_image(cub->graphics->mlx, cub->map->no, &cub->n_img.width, &cub->n_img.height);
	cub->s_img.img = mlx_xpm_file_to_image(cub->graphics->mlx, cub->map->so, &cub->s_img.width, &cub->s_img.height);
	cub->e_img.img = mlx_xpm_file_to_image(cub->graphics->mlx, cub->map->ea, &cub->e_img.width, &cub->e_img.height);
	cub->w_img.img = mlx_xpm_file_to_image(cub->graphics->mlx, cub->map->we, &cub->w_img.width, &cub->w_img.height);
	cub->n_img.address = NORTH;
	cub->s_img.address = SOUTH;
	cub->e_img.address = EAST;
	cub->w_img.address = WEST;
	if (!cub->n_img.img || !cub->s_img.img || !cub->e_img.img || !cub->w_img.img)
		map_errors(7, NULL);
}

int	get_matrix_size(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
		i++;
	return (i);
}

int	check_str_is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < 48 || str[i] > 57)
			return (0);
		i++;
	}
	return (EXIT_FAILURE);
}

void	ft_free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

//comprueba los valores de entrada de los parametros F y C
t_color	check_color_value(char	*color_value)
{
	t_color	color;
	char	**aux;
	char	*rgb_values;
	int		i;

	i = 0;
	while (color_value[i] && (color_value[i] == ' ' ||  color_value[i] == 'F' || color_value[i] == 'C' ))
		i++;
	rgb_values = color_value + i;
	if (ft_strlen(rgb_values) == 0)
		map_errors(8, NULL);
	aux = ft_split(rgb_values, ',');
	if (get_matrix_size(aux) != 3)
		map_errors(9, NULL);
	if (!check_str_is_num(aux[0]) || !check_str_is_num(aux[1]) || !check_str_is_num(aux[2]))
		map_errors(10, NULL);
	color.transparency = 0;
	color.red = ft_atoi(aux[0]);
	color.green = ft_atoi(aux[1]);
	color.blue = ft_atoi(aux[2]);
	if (color.red > 255 || color.green > 255 || color.blue > 255 || color.red < 0 || color.green < 0 || color.blue < 0)
		map_errors(11, NULL);
	ft_free_matrix(aux);
	return (color);
}

int	create_trgb(int t, int r, int g, int b) // pasar de R,G,B a decimal -> https://harm-smits.github.io/42docs/libs/minilibx/colors.html
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	get_pixel_color(t_cub *cub, t_textures *tex, int x, int y)
{
	char	*pixel;
	int		color;

	// Calcula la dirección del píxel en la memoria
	pixel = tex->address + (y * cub->graphics->line_length + x * (BPP / 8));

	// Obtiene el color del píxel
	color = *(int *)pixel;
	return (color);
}

void	put_pixel(t_cub *cub, int x, int y, int color) // https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html mas detalles al fianl de la pagina
{
	char	*dst;

	dst = cub->graphics->addr + (y * cub->graphics->line_length + x * (cub->graphics->bits_per_pixel / 8));
	*(unsigned int*) dst = color;
}

void	draw_sky_floor(t_cub *cub)
{
	int	y;
	int	x;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if(y < WIN_HEIGHT / 2)
			{
				put_pixel(cub, x, y, create_trgb(cub->sky_color.transparency, cub->sky_color.red, cub->sky_color.green, cub->sky_color.blue));
			}
			else
			{
				put_pixel(cub, x, y, create_trgb(cub->floor_color.transparency, cub->floor_color.red, cub->floor_color.green, cub->floor_color.blue));
			}
			x++;
		}
		y++;
	}
}

// Función principal
int	main(int argc, char **argv)
{
	t_cub *cub;  //Donde ira todo, tanto informacion del mapa y jugador
	char	**map_data;


	// Verificar la entrada y obtener datos del mapa
	check_input(argc, argv);
	map_data = read_map(argv[1]);
	cub = ft_calloc(1, sizeof(t_cub));
	if (!cub)
		return (EXIT_FAILURE);
	cub->map = check_map_data(create_map(), map_data);
	cub->sky_color = check_color_value(cub->map->c);
	cub->floor_color = check_color_value(cub->map->f);

	//verifico todos los datos(no quitar hasta el final, es muy util para depurar)
	printdoublepointer(cub->map->map);
	printdoublepointer(cub->map->all_map);
	printf("\n max x %zu", cub->map->max_x);
	printf("\n max y %zu", cub->map->max_y);
	printf("\n no %s", cub->map->no);
	printf("\n so %s", cub->map->so);
	printf("\n ea %s", cub->map->ea);
	printf("\n we %s", cub->map->we);
	printf("\n f %s", cub->map->f);
	printf("\n c %s", cub->map->c);
	printf("\n x %f", cub->map->player.x);
	printf("\n y %f", cub->map->player.y);
	printf("\n SKY_RGB %i %i %i", cub->sky_color.red, cub->sky_color.green, cub->sky_color.blue);
	printf("\n FLOOR_RGB %i %i %i\n", cub->floor_color.red, cub->floor_color.green, cub->floor_color.blue);
	cub->graphics = malloc(sizeof(t_mlx));
	if (!cub->graphics)
		map_errors(0, "");
	cub->graphics->mlx = mlx_init();
	cub->graphics->win = mlx_new_window(cub->graphics->mlx, WIN_WIDTH, WIN_HEIGHT, TITLE);
	cub->ray = malloc(sizeof(t_ray));
	if (cub->ray == NULL)
		map_errors(0, "");
	init_ray(cub->ray, locate_player(cub->map));
	//crear nueva imagen en la memoria con mlx_new_image
	cub->graphics->img = mlx_new_image(cub->graphics->mlx, WIN_WIDTH, WIN_HEIGHT);
	//mlx_get_data_addr permite modificar la imagen creada con mlx_new_image para editar pixel o texturas etc
	cub->graphics->addr = mlx_get_data_addr(cub->graphics->img, &cub->graphics->bits_per_pixel, &cub->graphics->line_length, &cub->graphics->endian);
	create_textures(cub); //carga en memoria las texturas y da error si no hay una textura o no se puede abrir
	draw_sky_floor(cub);
	//AQUI iria toodo el tema de rayos y renderizar el juego
	cast_rays(cub);
	//dibujar o mostrar en pantalla todo lo que pongamos
	mlx_put_image_to_window(cub->graphics->mlx, cub->graphics->win, cub->graphics->img, 0, 0);
	mlx_hook(cub->graphics->win, 17, 0, exit_game, cub->graphics); //pulsar sobre la "x" y cerrar juego. (mejorar el exit)
	mlx_loop(cub->graphics->mlx);


	// Bucle principal del juego
	/* while (1)
	{
		// Actualizar la posición del jugador
		ray->pos.x -= 1;
		while (++ray->pos.x < 1)
		{
			// Cálculos relacionados con la dirección y posición del rayo
			ray->camerax = 2 * ray->pos.x / WIN_WIDTH - 1;
			ray->pos.dirx = ray->pos.dirx + ray->plane.x * ray->camerax;
			ray->pos.diry = ray->pos.diry + ray->plane.y * ray->camerax;
			ray->map.x = (int) ray->pos.x;
			ray->map.y = (int) ray->pos.y;
			// Bucle para el lanzamiento de rayos y renderizado del juego
			if (ray->pos.dirx == 0)
				ray->deltadist.x = INFINITE;
			else
				ray->deltadist.x = fabs(1 / ray->pos.dirx);
			if (ray->pos.diry == 0)
				ray->deltadist.y = INFINITE;
			else
				ray->deltadist.y = fabs(1 / ray->pos.diry);
			if (ray->pos.dirx < 0)
			{
				// Más cálculos relacionados con el lanzamiento de rayos
				ray->pos.step.x = -1;
				ray->sidedist.x = (ray->pos.x - ray->map.x) * ray->deltadist.x;
			}
			else
			{
				ray->pos.step.x = 1;
				ray->sidedist.x = (ray->map.x + 1.0 - ray->pos.x) * ray->deltadist.x;
			}
			if (ray->pos.diry < 0)
			{
				ray->pos.step.y = -1;
				ray->sidedist.y = (ray->pos.y - ray->map.y) * ray->deltadist.y;
			}
			else
			{
				ray->pos.step.y = 1;
				ray->sidedist.y = (ray->map.y + 1.0 - ray->pos.y) * ray->deltadist.y;
			}
		}
		while (ray->pos.hit == 0)
		{
			if (ray->sidedist.x < ray->sidedist.y)
			{
				ray->sidedist.x += ray->deltadist.x;
				ray->map.x += ray->pos.step.x;
				ray->pos.side = 0;
			}
			else
			{
				ray->sidedist.y += ray->deltadist.y;
				ray->map.y += ray->pos.step.y;
				ray->pos.side = 1;
			}
			if (map->map[ray->map.x][ray->map.y] == '1')
				ray->pos.hit = 1;
		}
		if (ray->pos.side == 0)
			ray->perpwalldist = (ray->map.x - ray->pos.x + (1.0 - ray->pos.step.x) / 2.0) / ray->pos.dirx;
		else
			ray->perpwalldist = (ray->map.y - ray->pos.y + (1.0 - ray->pos.step.y) / 2.0) / ray->pos.diry;
		graphics->line_height = (int)(WIN_HEIGHT / ray->perpwalldist);
		graphics->draw_start = -graphics->line_height / 2 + WIN_HEIGHT / 2;
		if (graphics->draw_start < 0)
			graphics->draw_start = 0;
		graphics->draw_end = graphics->line_height / 2 + WIN_HEIGHT / 2;
		if (graphics->draw_end >= WIN_HEIGHT)
			graphics->draw_end = WIN_HEIGHT - 1;
		if (ray->pos.side == 0)
		{
			if (ray->pos.diry == -1)
				get_image(graphics->mlx, 'N');
			else
				get_image(graphics->mlx, 'S');
		}
		else
		{
			if (ray->pos.diry == -1)
				get_image(graphics->mlx, 'W');
			else
				get_image(graphics->mlx, 'E');
		}
	} */
	return (0);
}
