/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoteo-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 15:17:25 by aoteo-be          #+#    #+#             */
/*   Updated: 2021/11/12 12:36:19 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	len;
	static char		*response;
	unsigned char	i;

	if (s == NULL || f == NULL)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	response = malloc((len + 1) * sizeof(char));
	if (response == NULL)
		return (NULL);
	if (s == NULL || f == NULL)
		return (NULL);
	while (i < len)
	{
		response[i] = f(i, s[i]);
		i++;
	}
	response[i] = '\0';
	return (response);
}
