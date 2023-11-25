/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoteo-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 13:19:47 by aoteo-be          #+#    #+#             */
/*   Updated: 2021/11/11 12:11:06 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	int			i;
	char		*destiny;
	const char	*source;

	i = (int)n - 1;
	destiny = (char *)dst;
	source = (char *)src;
	if (n == 0 || source == destiny)
		return (dst);
	if (source > destiny)
		ft_memcpy(dst, src, n);
	else
	{
		while (i >= 0)
		{
			destiny[i] = source[i];
			i--;
		}
	}
	return (dst);
}
