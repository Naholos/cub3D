/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 00:04:56 by esamad-j          #+#    #+#             */
/*   Updated: 2023/11/20 22:47:51 by esamad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include "../mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

# define ERROR	"\33[31mError\n"

typedef struct s_max_values
{
	int	max_x;
	int	max_y;
}	t_max_values;

typedef struct s_player
{
	int	pos_x;
	int	pos_y;
}	t_player;

typedef struct s_map
{
	char		*no;
	char		*so;
	char		*ea;
	char		*we;
	char		*f;
	char		*c;
	char		**map;
	size_t		max_x;
	size_t		max_y;
	t_player	player;
}	t_map;

/* check_walls */
int		check_walls(t_map *map);
char	**get_rectangular_map(t_map *map);
void	remove_tmp_map(char **tmp);

/* map_errors */
void	map_errors(int i, char *parameter);
void	check_empty_line(char *line);
void	check_map_data(t_map *all_map, char **map_data);
void	check_map_param(char *line, char **param, char *param_name, int i);
void	check_no_parameter(t_map *map);
void	check_player_pos(t_map *all_map);

/* map_read.c */
char	**read_map(char *map_name);

#endif
