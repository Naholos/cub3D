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
			if (check_chars(m, m->map[y][x], x, y))
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
