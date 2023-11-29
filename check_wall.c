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

// Estructura para almacenar los valores máximos de x e y en el mapa
t_max_values	get_max_values(char **map)
{
	t_max_values	max_values;
	int				x;
	int				y;

	max_values.max_x = 0;
	max_values.max_y = 0;
	y = 0;

	// Recorre las filas del mapa
	while (map[y])
	{
		x = 0;

		// Recorre los caracteres en cada fila para encontrar el máximo x
		while (map[y][x])
			x++;
		// Actualiza max_x si se encuentra un valor mayor
		if (max_values.max_x < x)
			max_values.max_x = x;
		y++;
	}
	// El valor final de y es el máximo y
	max_values.max_y = y;
	return (max_values);
}

// Libera la memoria asignada para un mapa temporal
void	remove_tmp_map(char **tmp)
{
	int	i;

	i = 0;
	// Recorre las filas del mapa
	while (tmp[i] != NULL)
	{
		// Libera la memoria para cada fila
		free(tmp[i]);
		i++;
	}
	// Libera la memoria para el array de punteros
	free(tmp);
	tmp = NULL;
}

// Crea un mapa rectangular con dimensiones especificadas e inicialízalo con espacios
char	**create_rectangular_map(size_t max_x, size_t max_y)
{
	char	**tmp_map;
	size_t	x;
	size_t	y;

	// Asigna memoria para el array de punteros (filas)
	tmp_map = ft_calloc(max_y + 3, sizeof(char *));
	if (!tmp_map)
		map_errors(0, "");
	y = -1;
	// Recorre las filas
	while (++y < max_y + 2)
	{
		// Asigna memoria para cada fila e inicialízala con espacios
		tmp_map[y] = ft_calloc(max_x + 3, sizeof(char *));
		if (!tmp_map[y])
			map_errors(0, "");
		x = -1;
		// Recorre los caracteres en cada fila
		while (++x < max_x + 2)
			tmp_map[y][x] = ' ';
		tmp_map[y][x] = '\0';
	}
	// El último elemento del array de punteros se establece en NULL
	tmp_map[y] = NULL;
	return (tmp_map);
}

// Crea un mapa rectangular basado en el mapa original y actualiza max_x y max_y
char	**get_rectangular_map(t_map *map)
{
	char			**tmp_map;
	size_t			x;
	size_t			y;
	t_max_values	max_values;

	// Obtiene los valores máximos de x e y del mapa original
	max_values = get_max_values(map->map);
	map->max_x = max_values.max_x;
	map->max_y = max_values.max_y;
	// Crea un mapa rectangular con las dimensiones actualizadas
	tmp_map = create_rectangular_map(map->max_x, map->max_y);
	y = 0;
	// Copia los caracteres del mapa original al mapa rectangular
	while (++y < map->max_y + 1)
	{
		x = 0;
		// Copia los caracteres del mapa original, ajustando los índices
		while (++x < ft_strlen(map->map[y - 1]) + 1)
			tmp_map[y][x] = map->map[y - 1][x - 1];
	}
	return (tmp_map);
}

// Verifica las paredes en el mapa (caracteres '0', 'N', 'S', 'W', 'E') sin espacios adyacentes
int	check_walls(t_map *map)
{
	char			**tmp;
	int				x;
	int				y;
	t_max_values	max_values;

	y = -1;
	// Crea un mapa rectangular basado en el mapa original
	tmp = get_rectangular_map(map);
	// Obtiene los valores máximos de x e y del mapa rectangular
	max_values = get_max_values(tmp);
	// Recorre el mapa rectangular para verificar paredes sin espacios adyacentes
	while (++y < max_values.max_y)
	{
		x = -1;
		while (++x < max_values.max_x)
		{
			if (tmp[y][x] == '0' || tmp[y][x] == 'N' || tmp[y][x] == 'S' || tmp[y][x] == 'W' || tmp[y][x] == 'E')
				if (tmp[y + 1][x] == ' ' || tmp[y - 1][x] == ' ' || tmp[y][x + 1] == ' ' || tmp[y][x - 1] == ' ')
					// Si se encuentra una pared con un espacio adyacente, libera la memoria y devuelve -1
					return (remove_tmp_map(tmp), -1);
		}
	}
	// No se encontraron problemas, libera la memoria y devuelve 0
	remove_tmp_map(tmp);
	return (0);
}
