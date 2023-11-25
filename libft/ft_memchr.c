/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoteo-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 13:37:19 by aoteo-be          #+#    #+#             */
/*   Updated: 2021/11/12 12:36:19 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*response;
	size_t	i;
	char	ch;

	i = 0;
	ch = (char)c;
	if (!n)
		return (NULL);
	response = (char *)s;
	while ((i < n) && (response[i] != ch))
		i++;
	if (i == n)
	{
		if (ch == '\0')
			return (response + ft_strlen(response));
		else
			return (NULL);
	}
	return (response + i);
}
