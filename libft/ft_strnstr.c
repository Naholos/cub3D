/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoteo-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 13:14:18 by aoteo-be          #+#    #+#             */
/*   Updated: 2021/11/12 12:36:19 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	ln_needle;
	size_t	ln_haystack;
	size_t	i;
	char	*equal_haystack;

	equal_haystack = (char *)haystack;
	ln_haystack = ft_strlen(haystack);
	ln_needle = ft_strlen(needle);
	if (ln_haystack > len)
		ln_haystack = len;
	if (ln_needle > len || ln_needle > ln_haystack)
		return (NULL);
	if (*needle == '\0' || needle == haystack)
		return (equal_haystack);
	i = 0;
	while (i <= (ln_haystack - ln_needle))
	{
		if (!ft_strncmp(&equal_haystack[i], needle, ln_needle))
			return (equal_haystack + i);
		else
			i++;
	}
	return (NULL);
}
