
#include "cub.h"

int 	check_top_border(int i, int j, char **map)
{
	while (i >= 0) {
		if (map[i][j] == '1')
			return (1);
		if (map[i][j] != '2' && map[i][j] != 'N' && map[i][j] != 'E'
			&& map[i][j] != 'S' && map[i][j] != 'W' && map[i][j] != '0')
			return (0);
		i--;
	}
	return (0);
}

int 	check_left_border(int i, int j, char **map)
{
	while (j >= 0)
	{
		if (map[i][j] == '1')
			return (1);
		if (map[i][j] != '2' && map[i][j] != 'N' && map[i][j] != 'E'
			&& map[i][j] != 'S' && map[i][j] != 'W' && map[i][j] != '0')
			return (0);
		j--;
	}
	return (0);
}

int 	check_bot_border(int i, int j, char **map, t_game *game)
{
	int height;

	height = game->map_height;
	while (i < height)
	{
		if (map[i][j] == '1')
			return (1);
		if (map[i][j] != '2' && map[i][j] != 'N' && map[i][j] != 'E'
			&& map[i][j] != 'S' && map[i][j] != 'W' && map[i][j] != '0')
			return (0);
		i++;
	}
	return (0);
}

int 	check_right_border(int i, int j, char **map, t_game *game)
{
	int width;

	width = game->map_width;
	while (j < width)
	{
		if (map[i][j] == '1')
			return (1);
		if (map[i][j] != '2' && map[i][j] != 'N' && map[i][j] != 'E'
		&& map[i][j] != 'S' && map[i][j] != 'W' && map[i][j] != '0')
			return (0);
		j++;
	}
	return (0);
}

int 	check_borders(int i, int j, char **map, t_game *game)
{
	if (check_bot_border(i, j, map, game) && check_left_border(i, j , map) &&
		check_right_border(i, j, map, game) && check_top_border(i, j, map))
		return (1);
	return (0);
}

