/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listsort_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 13:50:38 by denis             #+#    #+#             */
/*   Updated: 2020/05/03 17:47:42 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int 		lstsize(t_sprite_list *head)
{
	int size;

	size = 0;
	while(head)
	{
		head = head->next;
		size++;
	}
	return (size);
}

static void		ft_listsplit(t_sprite_list *head, t_sprite_list **first, t_sprite_list **second)
{
	t_sprite_list *runner;

	runner = head;
	*first = head;
	*second = head->next;
	if (lstsize(head) < 2)
	{
		*first = head;
		*second = NULL;
	}
	else
	{
		while (runner->next && runner->next->next)
		{
			head = head->next;
			runner = runner->next->next;
		}
		*second = head->next;
		head->next = NULL;
	}
}

static t_sprite_list	*ft_merge(t_sprite_list *first, t_sprite_list *second)
{
	t_sprite_list *result;

	result = NULL;
	if (!first)
		return (second);
	if (!second)
		return (first);
	if (first->distance > second->distance)
	{
		result = first;
		result->next = ft_merge(first->next, second);
	}
	else
	{
		result = second;
		result->next = ft_merge(first, second->next);
	}
	return (result);
}

t_sprite_list			*mergesort_list(t_sprite_list *lst)
{
	t_sprite_list *first;
	t_sprite_list *second;

	if (lst == NULL || lst->next == NULL)
		return (lst);
	ft_listsplit(lst, &first, &second);
	first = mergesort_list(first);
	second = mergesort_list(second);
	return (ft_merge(first, second));
}
