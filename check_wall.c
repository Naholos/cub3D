/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 04:29:40 by esamad-j          #+#    #+#             */
/*   Updated: 2023/11/17 04:30:45 by esamad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

t_max_values	get_max_values(char **map)
{
	t_max_values	max_values;
	int				x;
	int				y;

	max_values.max_x = 0;
	max_values.max_y = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
			x++;
		if (max_values.max_x < x)
			max_values.max_x = x;
		y++;
	}
	max_values.max_y = y;
	return (max_values);
}

void	remove_tmp_map(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i] != NULL)
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
	tmp = NULL;
}

char	**create_rectangular_map(size_t max_x, size_t max_y)
{
	char	**tmp_map;
	size_t	x;
	size_t	y;

	tmp_map = ft_calloc(max_y + 3, sizeof(char *));
	if (!tmp_map)
		map_errors(0, "");
	y = -1;
	while (++y < max_y + 2)
	{
		tmp_map[y] = ft_calloc(max_x + 3, sizeof(char *));
		if (!tmp_map[y])
			map_errors(0, "");
		x = -1;
		while (++x < max_x + 2)
			tmp_map[y][x] = ' ';
		tmp_map[y][x] = '\0';
	}
	tmp_map[y] = NULL;
	return (tmp_map);
}

char	**get_rectangular_map(t_map *map)
{
	char			**tmp_map;
	size_t			x;
	size_t			y;
	t_max_values	max_values;

	max_values = get_max_values(map->map);
	map->max_x = max_values.max_x;
	map->max_y = max_values.max_y;
	tmp_map = create_rectangular_map(map->max_x, map->max_y);
	y = 0;
	while (++y < map->max_y + 1)
	{
		x = 0;
		while (++x < ft_strlen(map->map[y - 1]) + 1)
			tmp_map[y][x] = map->map[y - 1][x - 1];
	}
	return (tmp_map);
}

int	check_walls(t_map *map)
{
	char			**tmp;
	int				x;
	int				y;
	t_max_values	max_values;

	y = -1;
	tmp = get_rectangular_map(map);
	max_values = get_max_values(tmp);
	while (++y < max_values.max_y)
	{
		x = -1;
		while (++x < max_values.max_x)
		{
			if (tmp[y][x] == '0' || tmp[y][x] == 'N' || tmp[y][x] == 'S'
			|| tmp[y][x] == 'W' || tmp[y][x] == 'E')
				if (tmp[y + 1][x] == ' ' || tmp[y - 1][x] == ' '
				|| tmp[y][x + 1] == ' ' || tmp[y][x - 1] == ' ')
					return (remove_tmp_map(tmp), -1);
		}
	}
	remove_tmp_map(tmp);
	return (0);
}
