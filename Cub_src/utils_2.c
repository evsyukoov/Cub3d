/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 16:04:57 by denis             #+#    #+#             */
/*   Updated: 2020/07/11 14:51:02 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		str_endswith(char *s, char *set)
{
	char *s_end;
	char *set_end;

	s_end = s + ft_strlen(s);
	set_end = set + ft_strlen(set);
	while (s_end != s && *s_end == *set_end && set_end != set)
	{
		s_end--;
		set_end--;
	}
	if (set_end == set && *set == *s_end)
		return (1);
	return (0);
}

void	parse_remainder(t_game *game, t_list *lst)
{
	if (is_full_config(game))
		game->map = read_map(lst);
	else
		error("Wrong config data");
}

int		get_texture_index(char *str, char **path)
{
	int			i;
	static int	k;

	if (starts_with("S", str) && *(str + 1) == ' ' && ++k)
		i = SPRITE;
	else
	{
		if (starts_with("SO", str) && ++k)
			i = SOUTH;
		else if (starts_with("NO", str) && ++k)
			i = NORTH;
		else if (starts_with("WE", str) && ++k)
			i = WEST;
		else
		{
			i = EAST;
			k++;
		}
	}
	if (k > 5)
		error("Too much textures arguments!");
	*path = str + 2;
	if (i == 0 || i == 1 || i == 2 || i == 3)
		*path += 1;
	return (i);
}

int		is_starts_with_text(char *str)
{
	if (starts_with("NO", str) || starts_with("SO", str)
	|| starts_with("WE", str) || starts_with("EA", str)
	|| starts_with("S", str))
		return (1);
	return (0);
}

int		check_unexpected_symbols(t_game *game)
{
	int i;
	int j;
	int count;

	i = 0;
	count = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] != '2' && game->map[i][j] != 'N'
			&& game->map[i][j] != 'E' && game->map[i][j] != 'S'
			&& game->map[i][j] != 'W' && game->map[i][j] != '0'
			&& game->map[i][j] != ' ' && game->map[i][j] != '1')
				return (0);
			if (check_begin_pos(game->map[i][j]))
				count++;
			if (count > 1)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
