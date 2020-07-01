/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 20:12:00 by denis             #+#    #+#             */
/*   Updated: 2020/05/01 18:45:22 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *tmp;

	tmp = *lst;
	while (*lst)
	{
		tmp = tmp->next;
		del((*lst)->content);
		free((*lst));
		(*lst) = tmp;
	}
	(*lst) = NULL;
}
