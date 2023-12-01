/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 01:34:29 by esamad-j          #+#    #+#             */
/*   Updated: 2023/11/30 03:07:10 by esamad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

// Verifica el carácter en una posición específica del mapa y realiza acciones según el valor
int	check_chars(t_map *all_map, char value, int x, int y)
{
	// Verifica que el carácter sea válido ('1', '0', 'N', 'S', 'E', 'W' o espacio)
	if (value != '1' && value != '0' && value != 'N'
		&& value != 'S' && value != 'E' && value != 'W' && value != ' ')
		map_errors(3, "");
		// Si el carácter es la posición inicial del jugador ('N', 'S', 'E' o 'W'), actualiza la posición del jugador
	if (value == 'N' || value == 'S' || value == 'E' || value == 'W')
	{
		all_map->player.y = y;
		all_map->player.x = x;
		return (1);
	}
	// No es la posición inicial del jugador
	return (0);
}

// Verifica la posición del jugador en el mapa y maneja errores según las condiciones
void	check_player_pos(t_map *all_map)
{
	int		x;
	int		y;
	int		player_flag;

	y = -1;
	player_flag = 0;
	// Recorre el mapa para verificar la posición del jugador
	while (all_map->map[++y])
	{
		x = -1;
		while (all_map->map[y][++x])
			player_flag += check_chars(all_map, all_map->map[y][x], x, y);
	}
	// Verifica el número de jugadores en el mapa
	if (player_flag > 1)
		map_errors(5, "");
	if (!player_flag)
		map_errors(6, "");
}

// Lee el contenido de un archivo y lo divide en líneas para obtener el mapa
char	**read_file(int fd_map)
{
	char	**map;
	char	*lines;
	char	*tmp;

	tmp = get_next_line(fd_map);
	lines = malloc(1);
	if (!lines)
	{
		printf("%s%s\n", ERROR, "Error de asignación de memoria.\n");
		exit(EXIT_FAILURE);
	}
	// Lee el archivo línea por línea y concatena las líneas en un solo string
	while (tmp != NULL)
	{
		check_empty_line(tmp);
		lines = ft_strjoin_gnl(lines, tmp);
		free(tmp);
		tmp = get_next_line(fd_map);
	}
	free(tmp);
	close(fd_map);
	// Divide el string en líneas para obtener el mapa
	map = ft_split(lines, '\n');
	free(lines);
	return (map);
}

// Abre el archivo del mapa, maneja errores y llama a la función para leer el contenido del archivo
char	**read_map(char *map_name)
{
	char	**map_txt;
	int		fd_map;

	// Abre el archivo del mapa
	fd_map = open(map_name, O_RDONLY);
	if (fd_map == -1)
	{
		printf("%s%s\n", ERROR, "Error al abrir el archivo.\n");
		exit(EXIT_FAILURE);
	}
	// Verifica si el archivo del mapa está vacío
	if (read(fd_map, 0, 1) == 0)
	{
		printf("%s%s\n", ERROR, "Archivo de mapa vacío\n");
		exit(EXIT_FAILURE);
	}
	// Lee el contenido del archivo y obtiene el mapa
	map_txt = read_file(fd_map);
	return (map_txt);
}

// Verifica los datos del mapa, asigna valores a los parámetros y realiza verificaciones adicionales
t_map	*check_map_data(t_map *all_map, char **map_data)
{
	int	i;

	// Asigna el puntero del mapa a la posición después de las 6 primeras líneas de parámetros
	all_map->all_map = map_data;
	all_map->map = map_data + 6;
	i = -1;
	// Recorre las líneas de parámetros para asignar valores a las variables correspondientes
	while (map_data[++i] != NULL)
	{
		if (!ft_strncmp(map_data[i], "NO", 2))
			check_map_param(map_data[i], &(all_map->no), "NO", 3);
		else if (!ft_strncmp(map_data[i], "SO", 2))
			check_map_param(map_data[i], &(all_map->so), "SO", 3);
		else if (!ft_strncmp(map_data[i], "EA", 2))
			check_map_param(map_data[i], &(all_map->ea), "EA", 3);
		else if (!ft_strncmp(map_data[i], "WE", 2))
			check_map_param(map_data[i], &(all_map->we), "WE", 3);
		else if (!ft_strncmp(map_data[i], "F", 1))
			check_map_param(map_data[i], &(all_map->f), "F", 2);
		else if (!ft_strncmp(map_data[i], "C", 1))
			check_map_param(map_data[i], &(all_map->c), "C", 2);
	}

	// Realiza verificaciones adicionales y maneja errores
	check_no_parameter(all_map);
	check_player_pos(all_map);
	if (check_walls(all_map) == -1)
		map_errors(4, "");
	return (all_map);
}
