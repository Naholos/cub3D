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
# include <math.h>
//# include <mlx.h>
# include "../mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

# define DOWN	13
# define LEFT	0
# define RIGHT	2
# define SCAPE	53
# define UP		1

# define ERROR	".\33[31mError\n"

# define EAST	"./textures/ea_1.xpm"
# define NORTH	"./textures/no_1.xpm"
# define SOUTH	"./textures/so_1.xpm"
# define WEST	"./textures/we_1.xpm"

# define INFINITE 1e30

# define FOV	0.66

# define TEXT_DIM		64

# define TITLE		"cub3D"
# define WIN_HEIGHT	480
# define WIN_WIDTH	640

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

typedef struct s_mlx
{
	int		draw_start;
	int		draw_end;
	int		line_height;
	void	*img;
	void	*mlx;
	void	*win;
}	t_mlx;

typedef struct s_max_values
{
	int	max_x;
	int	max_y;
}	t_max_values;

typedef struct s_double
{
	double	x;
	double	y;
}	t_double;

typedef struct s_player
{
	int		hit;
	int		side;
	double	x;
	double	y;
	double	dirx;
	double	diry;
	t_coord	step;
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

typedef struct s_ray
{
	double		camerax;
	double		time;
	double		old_time;
	double		perpwalldist;
	t_coord		map;
	t_double	plane;
	t_double	sidedist;
	t_double	deltadist;
	t_player	pos;
}	t_ray;

/* check_walls */
int			check_walls(t_map *map);
char		**get_rectangular_map(t_map *map);
void		remove_tmp_map(char **tmp);

/* map_errors */
void		map_errors(int i, char *parameter);
void		check_empty_line(char *line);
t_map		*check_map_data(t_map *all_map, char **map_data);
void		check_map_param(char *line, char **param, char *param_name, int i);
void		check_no_parameter(t_map *map);
void		check_player_pos(t_map *all_map);

/* map_read.c */
int			check_chars(t_map *all_map, char value, int x, int y);
char		**read_map(char *map_name);

/* ray.c */
void		get_image(t_mlx *mlx, char symbol);
void		init_ray(t_ray *ray, t_player *player);
t_player	*locate_player(t_map *all_map);

#endif
