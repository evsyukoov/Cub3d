/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 19:42:40 by denis             #+#    #+#             */
/*   Updated: 2020/05/02 18:27:39 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *last;

	if (!(*lst))
	{
		*lst = new;
		(*lst)->next = NULL;
		return ;
	}
	last = ft_lstlast((*lst));
	last->next = new;
	new->next = NULL;
}
