/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 23:56:12 by esamad-j          #+#    #+#             */
/*   Updated: 2023/11/21 17:59:32 by esamad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

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

int	main(int argc, char **argv)
{
	char	**map_data;
	t_map	*map;
	t_mlx	*graphics;
	t_ray	*ray;

	check_input(argc, argv);
	map_data = read_map(argv[1]);
	map = check_map_data(create_map(), map_data);
	graphics = malloc(sizeof(t_mlx));
	if (graphics == NULL)
		map_errors(0, "");
	graphics->mlx = mlx_init();
	graphics->win = mlx_new_window(graphics->mlx, WIN_WIDTH, WIN_HEIGHT, TITLE);
	ray = malloc(sizeof(t_ray));
	if (ray == NULL)
		map_errors(0, "");
	init_ray(ray, locate_player(map));
	while (1)
	{
		ray->pos.dirx = -1;
		while (++ray->pos.x < WIN_WIDTH)
		{
			ray->camerax = 2 * ray->pos.dirx / (double) WIN_WIDTH - 1;
			ray->pos.dirx = ray->pos.dirx + ray->plane.x * ray->camerax;
			ray->pos.diry = ray->pos.diry + ray->plane.y * ray->camerax;
			ray->map.x = (int) ray->pos.x;
			ray->map.y = (int) ray->pos.y;
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
			ray->perpwalldist = (ray->sidedist.x - ray->deltadist.x);
		else
			ray->perpwalldist = (ray->sidedist.y - ray->deltadist.y);
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
	}
	return (0);
}
