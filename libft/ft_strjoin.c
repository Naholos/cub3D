/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoteo-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 13:11:02 by aoteo-be          #+#    #+#             */
/*   Updated: 2021/11/12 12:36:19 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*concat;	

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	concat = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (concat == NULL)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1))
	{
		concat[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < ft_strlen(s2))
	{
		concat[i + j] = s2[j];
		j++;
	}
	concat[i + j] = '\0';
	return (concat);
}
