/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoteo-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 14:09:27 by aoteo-be          #+#    #+#             */
/*   Updated: 2021/11/11 12:11:06 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t n)
{
	unsigned char	*solution;
	size_t			i;

	i = 0;
	solution = b;
	while (i < n)
	{
		solution[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
