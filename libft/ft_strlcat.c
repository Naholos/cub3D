/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoteo-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 15:14:54 by aoteo-be          #+#    #+#             */
/*   Updated: 2021/11/12 12:36:19 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len_dst;
	size_t	len_src;
	size_t	new_len_dst;

	i = 0;
	len_dst = ft_strlen(dst);
	new_len_dst = len_dst;
	len_src = ft_strlen(src);
	if (dstsize == 0)
		return (len_src);
	while (new_len_dst < dstsize - 1 && src[i] != '\0')
	{
		dst[new_len_dst] = src[i];
		i++;
		new_len_dst++;
	}
	if (dstsize >= len_dst)
		dst[new_len_dst] = '\0';
	if (dstsize < len_dst)
		return (len_src + dstsize);
	else
		return (len_dst + len_src);
}
