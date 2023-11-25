/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoteo-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 13:23:47 by aoteo-be          #+#    #+#             */
/*   Updated: 2021/11/12 12:36:19 by aoteo-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	digits(long int n)
{
	long int	divisor;
	size_t		i;

	if (!n)
		return (1);
	divisor = 10e10;
	i = 0;
	while (n / divisor == 0)
		divisor /= 10;
	while (divisor != 0)
	{
		n %= divisor;
		divisor /= 10;
		i++;
	}
	return (i);
}

static void	digit_to_char(long int n, int minus, size_t divisor, char *response)
{
	size_t	i;

	i = 0;
	if (minus == 1)
	{
		*response = '-';
		i++;
	}
	while (divisor != 0)
	{
		*(response + i) = (int)(n / divisor) + '0';
		n %= divisor;
		divisor /= 10;
		i++;
	}
	*(response + i) = '\0';
}

char	*ft_itoa(int n)
{
	char		*response;
	long int	long_n;
	int			minus;
	size_t		digit_number;
	size_t		divisor;

	divisor = 1;
	minus = 0;
	long_n = (long int)n;
	if (long_n < 0)
	{
		minus = 1;
		long_n = (-1) * long_n;
	}
	digit_number = digits(long_n);
	response = malloc((digit_number + minus + 1) * sizeof(char));
	if (response == NULL)
		return (NULL);
	while (digit_number > 1)
	{
		divisor *= 10;
		digit_number--;
	}
	digit_to_char(long_n, minus, divisor, response);
	return (response);
}
