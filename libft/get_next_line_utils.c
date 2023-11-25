/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:57:04 by esamad-j          #+#    #+#             */
/*   Updated: 2023/11/16 04:25:11 by esamad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_gnl(char *str1, char *str2)
{
	size_t	i;
	size_t	j;
	char	*new_str;

	i = 0;
	j = 0;
	if (!str1)
		str1 = ft_calloc(1, 1);
	if (!str1 || !str2)
		return (NULL);
	new_str = ft_calloc(sizeof(char), (ft_strlen(str1) + ft_strlen(str2) + 1));
	while (str1[i] != '\0')
	{
		new_str[i] = str1[i];
		i++;
	}
	while (str2[j] != '\0')
	{
		new_str[i] = str2[j];
		i++;
		j++;
	}
	new_str[i] = '\0';
	free(str1);
	return (new_str);
}

int	ft_strchr_gnl(const char *s, char c)
{
	int		i;
	char	aux;

	if (!s)
		return (-1);
	i = 0;
	aux = c;
	while (s[i] != '\0')
	{
		if (s[i] == aux)
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

size_t	ft_strlen(const char *s)
{
	size_t	cont;

	if (!s)
		return (0);
	cont = 0;
	while (s[cont] != '\0')
		cont++;
	return (cont);
}
