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

t_player	*locate_player(t_map *all_map)
{
	int			p_found;
	t_player	*p;

	p_found = 0;
	p = malloc(sizeof(t_player));
	if (p == NULL)
		map_errors(0, "");
	p->y = -1;
	while (all_map->map[++p->y])
	{
		p->x = -1;
		while (all_map->map[p->y][++p->x])
		{
			if (check_chars(all_map, all_map->map[p->y][p->x], p->x, p->y))
			{
				p_found = 1;
				break ;
			}
		}
		if (p_found)
			break ;
	}
	return (p);
}

void	init_ray(t_ray *ray, t_player *player)
{
	ray->pos.x = player->x;
	ray->pos.y = player->y;
	ray->plane.x = 0;
	ray->plane.y = FOV;
}
