/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoteo-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 15:20:09 by aoteo-be          #+#    #+#             */
/*   Updated: 2021/11/12 12:36:19 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	size_t	len;
	int		pos;
	char	ch;

	len = ft_strlen(s);
	pos = -1;
	i = 0;
	ch = (char)c;
	while (i < len)
	{
		if (s[i] == ch)
			pos = i;
		i++;
	}
	if (c == '\0')
		return ((char *)(s + i));
	if (pos != -1)
		return ((char *)(s + pos));
	return (NULL);
}
