/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoteo-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 13:27:14 by aoteo-be          #+#    #+#             */
/*   Updated: 2021/11/12 12:36:19 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first;
	t_list	*final;

	final = NULL;
	if (!lst || !f)
		return (NULL);
	while (lst)
	{
		first = ft_lstnew(f(lst->content));
		if (first == NULL)
		{
			ft_lstclear(&first, (*del));
			return (NULL);
		}
		ft_lstadd_back(&final, first);
		lst = lst->next;
	}
	return (final);
}
