/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 20:24:10 by denis             #+#    #+#             */
/*   Updated: 2020/05/04 16:19:18 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *new_head;
	t_list *current;

	new_head = ft_lstnew(f(lst->content));
	if (!new_head || !lst || !f)
		return (0);
	lst = lst->next;
	while (lst)
	{
		current = ft_lstnew(f(lst->content));
		if (!current)
		{
			ft_lstclear(&new_head, del);
			return (0);
		}
		ft_lstadd_back(&new_head, current);
		lst = lst->next;
	}
	return (new_head);
}
