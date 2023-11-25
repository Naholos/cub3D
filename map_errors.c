/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 12:07:28 by aoteo-be          #+#    #+#             */
/*   Updated: 2023/11/22 04:20:15 by esamad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

static int	check_line_param(char *line)
{
	static int	dup[6] = {0, 0, 0, 0, 0, 0};

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
	return (0);
}

void	map_errors(int i, char *parameter)
{
	printf("%s", ERROR);
	if (i == 0)
		printf("Memory error.");
	else if (i == 1)
		printf("parameter %s duplicated.", parameter);
	else if (i == 2)
		printf("parameter %s not defined.", parameter);
	else if (i == 3)
		printf("Unknown map symbol.");
	else if (i == 4)
		printf("Map should be surrounded by walls.");
	else if (i == 5)
		printf("Multiple players found");
	else if (i == 6)
		printf("No player position found");
	printf("\n");
	exit (EXIT_FAILURE);
}

static int	line_with_1_0(const char *line)
{
	int	i;

	i = 0;
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

void	check_empty_line(char *line)
{
	static int	count = 0;
	static int	finish_map = 0;
	static int	init_map = 0;
	size_t		line_len;

	line_len = ft_strlen(line);
	if (count == 6 && line_len > 1 && !init_map && line_with_1_0(line))
		init_map = 1;
	if (count < 6 && line_len > 1 && check_line_param(line))
		count++;
	if (init_map && line_len == 1 && !finish_map)
		finish_map++;
	if ((line_len > 1 || *line != '\n') && finish_map)
	{
		printf("%s%s\n", ERROR, "Empty line in map.\n");
		exit(EXIT_FAILURE);
	}
}

void	check_map_param(char *line, char **param, char *param_name, int i)
{
	if (*param != NULL)
		map_errors(1, param_name);
	*param = malloc(sizeof(char) * (ft_strlen(line) + 1) - i);
	if (*param == NULL)
		map_errors(0, "");
	ft_memcpy(*param, line + i, ft_strlen(line) - i);
}
