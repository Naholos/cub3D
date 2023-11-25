/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoteo-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 13:20:14 by aoteo-be          #+#    #+#             */
/*   Updated: 2021/11/12 12:36:19 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*destiny;
	const unsigned char	*source;

	i = 0;
	destiny = dst;
	source = src;
	if (src == NULL)
		return (NULL);
	while (i < n)
	{
		destiny[i] = source[i];
		i++;
	}
	destiny[i] = '\0';
	return (dst);
}
