/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 19:59:59 by esamad-j          #+#    #+#             */
/*   Updated: 2023/11/14 01:46:41 by esamad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_read(int fd, char *saved)
{
	char	*buffer;
	int		byte_read;

	byte_read = 1;
	if (ft_strchr_gnl(saved, 10) != -1)
		return (saved);
	buffer = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while ((ft_strchr_gnl(saved, 10) == -1) && byte_read)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == 0)
			break ;
		if (byte_read == -1)
		{
			free(buffer);
			free(saved);
			return (NULL);
		}
		buffer[byte_read] = '\0';
		saved = ft_strjoin_gnl(saved, buffer);
	}
	free(buffer);
	return (saved);
}

char	*save_remain(char *saved)
{
	char	*temp;
	int		i;

	if (!saved)
		return (NULL);
	i = 0;
	while (saved[i] && saved[i] != '\n')
		i++;
	if (!saved[i] || !saved[i + 1])
	{
		free(saved);
		return (NULL);
	}
	if (saved[i])
		i++;
	temp = ft_strdup(&saved[i]);
	free(saved);
	return (temp);
}

char	*first_line(char *saved)
{
	int		i;
	char	*line;

	if (!saved)
		return (NULL);
	i = 0;
	while (saved[i] != '\n' && saved[i])
		i++;
	if (saved[i])
		i++;
	line = ft_calloc((i + 1), sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (saved[i] && saved[i] != '\n')
	{
		line[i] = saved[i];
		i++;
	}
	if (saved[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*line;

	saved = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	saved = ft_read(fd, saved);
	line = first_line(saved);
	saved = save_remain(saved);
	return (line);
}

/* int	main(void)
{
	char *leido;
	int fd;
	fd = open("hola.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("cagaste, ERROR EN OPEN");
		return (0);
	}
	leido = get_next_line(fd);
	printf("---main---\n");
	while (leido)
	{
		printf("%s", leido);
		fflush(stdin);
		free(leido);
		leido = get_next_line(fd);
	}

	free(leido);
	close(fd);

	return (0);
} */