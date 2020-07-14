/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 17:53:39 by denis             #+#    #+#             */
/*   Updated: 2020/07/10 17:54:56 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_sprite_list	*lstlast(t_sprite_list *head)
{
	t_sprite_list *tmp;

	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void			lstadd_back(t_sprite_list **head, t_sprite_list *node)
{
	t_sprite_list *last;

	if (!(*head))
	{
		(*head) = node;
		(*head)->next = NULL;
		return ;
	}
	last = lstlast((*head));
	last->next = node;
	node->next = NULL;
}

t_sprite_list	*create_new_node(int x, int y)
{
	t_sprite_list *node;

	if (!(node = (t_sprite_list*)malloc(sizeof(t_sprite_list))))
		return (0);
	node->x = x + 0.5;
	node->y = y + 0.5;
	node->next = NULL;
	return (node);
}

void			init_sprite_list(t_game *game)
{
	int				i;
	int				j;
	char			**map;
	t_sprite_list	*node;

	i = 0;
	map = game->map;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '2')
			{
				node = create_new_node(j, i);
				lstadd_back(&(game->sprites), node);
			}
			j++;
		}
		i++;
	}
}

t_sprite_list	*lstget(t_sprite_list *head, int index)
{
	int i;

	i = 0;
	while (i < index && head)
	{
		i++;
		head = head->next;
	}
	if (index <= -1)
		return (0);
	return (head);
}
