/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoteo-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 13:17:06 by aoteo-be          #+#    #+#             */
/*   Updated: 2021/11/12 12:36:19 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	write_char(int divisor, long ln, int fd)
{
	char	c;

	while (!(ln / divisor))
		divisor = divisor / 10;
	while (divisor > 0)
	{
		c = ln / divisor + '0';
		write(fd, &c, 1);
		ln %= divisor;
		divisor = divisor / 10;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	int		divisor;
	long	ln;
	char	c;

	ln = n;
	divisor = 1000000000;
	if (!ln)
	{
		c = '0';
		write(fd, &c, 1);
	}
	else
	{
		if (ln < 0)
		{
			c = '-';
			write(fd, &c, 1);
			ln *= -1;
		}
		write_char(divisor, ln, fd);
	}
}
