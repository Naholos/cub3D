/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 00:04:56 by esamad-j          #+#    #+#             */
/*   Updated: 2023/12/11 12:36:39 by esamad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
# include <mlx.h>
//# include "../mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

# define BPP	32
# define DOWN	13
# define LEFT	0
# define RIGHT	2
# define SCAPE	53
# define UP		1

# define ERROR	"\33[31mError\n"

# define INFINITE 1e30

# define FOV	0.66

#define MOVE_SPEED 0.05

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
	void	*img;				//necesario para imprimir pixeles en imagen -> https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		draw_start;
	int		draw_end;
	int		line_height;
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
	double	x; //pos inicial de jugador 
	double	y; //pos inicial de jugador 
	double	dirx;
	double	diry;
	t_coord	step;
}	t_player;

typedef struct s_map
{
	char		*no; //guardar las direcciones de las texturas
	char		*so;
	char		*ea;
	char		*we;
	char		*f; //guardar los valores de colores
	char		*c;
	char		**map; //guardar solo mapa
	char		**all_map; //guardar mapa con datos
	size_t		max_x; //maximo de largo
	size_t		max_y; //maximo de alto
	t_player	player; // posicion del jugador
}	t_map;

typedef struct s_ray
{
	double		camerax;
	double		time;
	double		old_time;
	double		perpwalldist;
	double 		wallx;
	
	int			draw_start;
	int			draw_end;
	int			line_height;
	t_coord		map;
	t_double	plane;
	t_double	sidedist;
	t_double	deltadist;
	t_player	pos;
}	t_ray;

typedef struct s_textures
{
	char	*address;
	int		height;
	int		width;
	void	*img;
	int		*text_value;
	int bpp;
	int line_len;
	int endian;

}	t_textures;

typedef struct s_color
{
	int	transparency;
	int	red;
	int	green;
	int	blue;
}	t_color;

typedef struct s_cub
{
	t_map			*map;
	t_textures		n_img;
	t_textures		s_img;
	t_textures		e_img;
	t_textures		w_img;
	t_color			sky_color;
	t_color			floor_color;
	t_mlx			*graphics;
	t_ray			*ray;
}	t_cub;

/* check_walls.c */
int			check_walls(t_map *map);
char		**get_rectangular_map(t_map *map);
void		remove_tmp_map(char **tmp);

/* cub3D.c */
int			get_pixel_color(t_cub *cub, t_textures *tex, int x, int y);
void		put_pixel(t_cub *cub, int x, int y, int color);

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
void	init_ray(t_ray *ray, t_cub *cub);
void		cast_rays(t_cub *cub);
t_player	*locate_player(t_map *all_map);

#endif
