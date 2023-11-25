/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoteo-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 09:38:05 by aoteo-be          #+#    #+#             */
/*   Updated: 2021/11/12 12:36:19 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	first(const char *s1, const char *set, size_t len_s1)
{
	size_t	i;
	size_t	j;
	size_t	count;
	size_t	len_set;

	len_set = ft_strlen(set);
	i = 0;
	count = 0;
	while (i < len_s1)
	{
		j = 0;
		while (j < len_set)
		{
			if (*(s1 + i) == *(set + j))
				break ;
			j++;
		}
		if (j < len_set)
			count++;
		else
			break ;
		i++;
	}
	return (count);
}

static size_t	last(const char *s1, const char *set, size_t len, size_t offset)
{
	size_t	i;
	size_t	j;
	size_t	count;
	size_t	len_set;

	len_set = ft_strlen(set);
	i = len - 1;
	count = 0;
	while (i > offset)
	{
		j = 0;
		while (j < len_set)
		{
			if (*(s1 + i) == *(set + j))
				break ;
			j++;
		}
		if (j < len_set)
			count++;
		else
			break ;
		i--;
	}
	return (count);
}

char	*ft_strtrim(const char *s1, char const *set)
{
	size_t	len_s1;
	size_t	start;
	size_t	end;	
	char	*response;

	if (s1 == NULL || set == NULL)
		return (NULL);
	len_s1 = ft_strlen(s1);
	if (set == s1 || *s1 == '\0')
	{
		response = malloc(sizeof(char));
		if (response == NULL)
			return (NULL);
		*response = '\0';
		return (response);
	}
	start = first(s1, set, len_s1);
	end = last(s1, set, len_s1, start);
	response = malloc((len_s1 - end - start + 1) * sizeof(char));
	if (response == NULL)
		return (NULL);
	ft_memcpy(response, s1 + start, (len_s1 - end - start));
	*(response + len_s1 - end - start) = '\0';
	return (response);
}
