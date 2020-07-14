/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 17:53:36 by denis             #+#    #+#             */
/*   Updated: 2020/07/11 13:34:10 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	**aligne_map(char **map)
{
	int		max_width;
	int		max_height;
	char	**aligned_map;
	int		i;
	char	*extra;

	max_width = find_max_width(map);
	max_height = find_max_height(map);
	aligned_map = (char**)malloc(sizeof(char*) * (find_max_height(map) + 1));
	i = 0;
	while (i < max_height)
	{
		if ((int)ft_strlen(map[i]) < max_width)
		{
			extra = extra_spaces(ft_strlen(map[i]), max_width);
			aligned_map[i] = ft_strjoin(map[i], extra);
			free(extra);
		}
		else
			aligned_map[i] = ft_strdup(map[i]);
		free(map[i++]);
	}
	aligned_map[i] = 0;
	free(map);
	return (aligned_map);
}

char	**read_map(t_list *lst)
{
	size_t	size;
	t_list	*tmp;
	char	**map;
	int		i;

	size = ft_lstsize(lst);
	i = 0;
	map = (char**)malloc(sizeof(char*) * (size + 1));
	while (lst)
	{
		tmp = lst;
		map[i] = (char*)lst->content;
		i++;
		lst = lst->next;
		free(tmp);
	}
	map[i] = NULL;
	return (aligne_map(map));
}

int		find_max_height(char **map)
{
	int i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int		find_max_width(char **map)
{
	int		i;
	int		len;
	int		max_width;

	i = 0;
	max_width = -1;
	while (map[i])
	{
		len = (int)ft_strlen(map[i]);
		if (len > max_width)
			max_width = len;
		i++;
	}
	return (max_width);
}

void	check_map(t_game *game)
{
	int		i;
	int		j;
	int		is_player;

	is_player = 0;
	game->map_width = find_max_width(game->map);
	game->map_height = find_max_height(game->map);
	i = 0;
	if (!check_unexpected_symbols(game))
		error("Map error!");
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if ((game->map)[i][j] == '0' || check_begin_pos(game->map[i][j]))
				check_borders(i, j, game->map, game);
			if (check_begin_pos(game->map[i][j]) && ++is_player)
				init_start_pos(game, game->map[i][j], i, j);
			j++;
		}
		i++;
	}
	if (!is_player)
		error("No player on map");
}
