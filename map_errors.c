/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 12:07:28 by aoteo-be          #+#    #+#             */
/*   Updated: 2023/11/30 23:17:28 by esamad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

// Verifica si una línea contiene un parámetro de configuración del mapa y realiza un seguimiento de duplicados
static int	check_line_param(char *line)
{
	// Array estático para rastrear la cantidad de duplicados de cada parámetro
	static int dup[6] = {0, 0, 0, 0, 0, 0};
	// Compara la línea con los diferentes parámetros y actualiza el contador de duplicados
	if (!ft_strncmp(line, "NO", 2))
		return (dup[0]++, 1);
	else if (!ft_strncmp(line, "SO", 2))
		return (dup[1]++, 1);
	else if (!ft_strncmp(line, "WE", 2))
		return (dup[2]++, 1);
	else if (!ft_strncmp(line, "EA", 2))
		return (dup[3]++, 1);
	else if (!ft_strncmp(line, "F ", 1))
		return (dup[4]++, 1);
	else if (!ft_strncmp(line, "C ", 1))
		return (dup[5]++, 1);
	// Si no es un parámetro reconocido, devuelve 0
	return (0);
}

// Imprime mensajes de error según el código de error proporcionado y sale del programa
void	map_errors(int i, char *parameter)
{
	printf("%s", ERROR);
	// Imprime mensajes de error específicos según el código de error
	if (i == 0)
		printf("Error de memoria.");
	else if (i == 1)
		printf("parámetro %s duplicado.", parameter);
	else if (i == 2)
		printf("parámetro %s no definido.", parameter);
	else if (i == 3)
		printf("Símbolo de mapa desconocido.");
	else if (i == 4)
		printf("El mapa debe estar rodeado por paredes.");
	else if (i == 5)
		printf("Se encontraron múltiples jugadores.");
	else if (i == 6)
		printf("No se encontró posición de jugador.");
	else if (i == 7)
		printf("Path to textures does not exist or cannot be accessed");
	else if (i == 8)
		printf("Empty value for sky/floor");
	else if (i == 9)
		printf("Value must be in R,G,B");
	else if (i == 10)
		printf("All value of R,G,B must be a digit");
	else if (i == 11)
		printf("R.G.B value must be between (0 to 255)");
	printf("\n");
	// Sale del programa con código de error
	exit(EXIT_FAILURE);
}

// Verifica si una línea contiene solo '1', '0', espacios y caracteres de jugador
static int	line_with_1_0(const char *line)
{
	int i = 0;

	while (line[i] != '\0')
	{
		if (line[i] == '1' || line[i] == '0' || line[i] == ' '
			|| line[i] == '\n' || line[i] == 'N' || line[i] == 'W'
			|| line[i] == 'E' || line[i] == 'S')
			i++;
		else
			return (0);
	}
	return (1);
}

// Verifica si una línea está vacía o contiene solo espacios y caracteres de jugador
void check_empty_line(char *line)
{
	static int	count = 0;
	static int	finish_map = 0;
	static int	init_map = 0;
	size_t		line_len;

	line_len = ft_strlen(line);
	// Verifica si la línea es válida para iniciar el mapa
	if (count == 6 && line_len > 1 && !init_map && line_with_1_0(line))
		init_map = 1;
	// Verifica si la línea es un parámetro de configuración del mapa
	if (count < 6 && line_len > 1 && check_line_param(line))
		count++;
	// Verifica si la línea indica el final del mapa
	if (init_map && line_len == 1 && !finish_map)
		finish_map++;
	// Verifica si hay una línea vacía después del final del mapa
	if ((line_len > 1 || *line != '\n') && finish_map)
	{
		printf("%s%s\n", ERROR, "Línea vacía en el mapa.\n");
		exit(EXIT_FAILURE);
	}
}

// Verifica y asigna un parámetro de configuración del mapa
void	check_map_param(char *line, char **param, char *param_name, int i)
{
	// Verifica si el parámetro ya ha sido asignado
	if (*param != NULL)
		map_errors(1, param_name);
	// Asigna memoria para el parámetro y copia el valor desde la línea
	*param = malloc(sizeof(char) * (ft_strlen(line) + 1) - i);
	if (*param == NULL)
		map_errors(0, "");
	ft_memcpy(*param, line + i, ft_strlen(line) - i);
}
