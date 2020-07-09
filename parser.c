/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 19:39:19 by denis             #+#    #+#             */
/*   Updated: 2020/06/04 15:37:35 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_list *reader(int fd)
{
	t_list	*lst;
	t_list	*node;
	char	*line;
	char 	*str;

	lst = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		str = ft_strdup(line);
		if (!(node = ft_lstnew(str)))
			return (0);
		ft_lstadd_back(&lst, node);
		free(line);
	}
	str = ft_strdup(line);
	if (!(node = ft_lstnew(str)))
		return (0);
	ft_lstadd_back(&lst, node);
	free(line);
	return (lst);
}

void 	error(char *message)
{
	ft_putstr_fd(message, 2);
	exit(0);
}

void 	init_resolution(t_game *game, char *string)
{
	int resolution[2];
	int i;

	i = 0;
	string += 1;
	while (i < 2) {
		skip_spaces(&string);
		resolution[i] = ft_atoi(string);
		string += digit_len(string);
		i++;
	}
	skip_spaces(&string);
	if (resolution[0] <= 0 || resolution[1] <= 0 || *string)
		error("Wrong screen resolution string");
	game->win_height = resolution[1];
	game->win_width = resolution[0];
}

int 	parse_color(char *string)
{
	int rgb[3];
	int i;

	string++;
	i = 0;
	while (i < 3)
	{
		while (*string == ' ')
			string++;
		if (!ft_isdigit(*string))
			error("Wrong color string");
		rgb[i] = ft_atoi(string);
		string += digit_len(string);
		while (*string == ' ' && *string)
			string++;
		if (*string != ',' && *string != '\0')
			error("Wrong color string");
		string++;
		i++;
	}
	return (rgb_to_int(rgb[0], rgb[1], rgb[2]));
}

void 	load_textures(t_game *game, char *str, t_texture **text)
{
	int i;
	char *path;

	if (starts_with("S", str) && !starts_with("SO", str)) {
		i = SPRITE;
		path = str + 1;
	}
	else {
		if (starts_with("SO", str))
			i = SOUTH;
		else if (starts_with("NO", str))
			i = NORTH;
		else if (starts_with("WE", str))
			i = WEST;
		else
			i = EAST;
		path = str + 2;
	}
	skip_spaces(&path);
	text[i]->img = mlx_xpm_file_to_image(game->mlx, path, &(text[i]->width), &(text[i]->height));
	if (!text[i]->img) {
		perror(path);
		exit (0);
	}
	text[i]->addr = mlx_get_data_addr(text[i]->img, &(text[i]->bits_per_pixel), &(text[i]->line_length),
									  &(text[i]->endian));
}

int 	init_default_config(t_game *game)
{
	int i;
	t_texture **textures;
	t_texture *texture;

	i = 0;
	if (!(textures = (t_texture**)malloc(sizeof(t_texture*) * 5)))
		return (0);
	game->textures = textures;
	while (i < 5)
	{
		texture = (t_texture*)malloc(sizeof(t_texture));
		(game->textures)[i] = texture;
		game->textures[i]->img = NULL;
		i++;
	}
	game->win_width = DEFAULT;
	game->win_height = DEFAULT;
	game->floor_color = DEFAULT;
	game->ceiling_color = DEFAULT;
	return (1);
}

int 	is_full_config(t_game *game)
{
	int i;

	i = 0;
	if (game->win_height == DEFAULT || game->win_width == DEFAULT
	|| game->floor_color == DEFAULT || game->ceiling_color == DEFAULT)
		return (0);
	while (i < 5)
	{
		if (game->textures[i]->img == NULL)
			return (0);
		i++;
	}
	return (1);
}

int 	parse_config(t_list *lst, t_game *game)
{
	t_list *tmp;

	while (lst)
	{
		//printf("height = %d\n", game->win_height);
		tmp = lst;
		if (starts_with("R", lst->content))
			init_resolution(game, (char*)lst->content);
		else if (starts_with("F", lst->content))
			game->floor_color = parse_color((char*)lst->content);
		else if (starts_with("C", lst->content))
			game->ceiling_color = parse_color((char*)lst->content);
		else if (starts_with("NO", lst->content) || starts_with("SO", lst->content)
		|| starts_with("WE", lst->content) || starts_with("EA", lst->content)
		|| starts_with("S", lst->content)) {
			load_textures(game, (char*)lst->content, game->textures);
		} else{
			if (*(char*)(lst->content) != '\0')
			{
				if (is_full_config(game)) {
					game->map = read_map(lst);
					break ;
				}
				else
					error("Wrong config data");
			}
		}
		lst = lst->next;
		free(tmp);
	}
	return (1);
}

char 	*extra_spaces(int len, int max_width)
{
	char *str;
	int i;

	str = (char*)malloc(sizeof(char) * (max_width - len + 1));
	i = 0;
	while (len < max_width) {
		str[i++] = ' ';
		len++;
	}
	str[i] = '\0';
	return (str);
}

char 	**aligne_map(char **map)
{
	int max_height;
	int max_width;
	char **aligned_map;
	int i;
	char *extra;

	max_width = find_max_width(map);
	max_height = find_max_height(map);
	aligned_map = (char**)malloc(sizeof(char*) * (max_height + 1));
	i = 0;
	while (i < max_height)
	{
		aligned_map[i] = (char*)malloc(sizeof(char) * (max_width + 1));
		if (ft_strlen(map[i]) < max_width)
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

char 	**read_map(t_list *lst)
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
		map[i] = ft_strdup(lst->content);
		free(lst->content);
		i++;
		lst = lst->next;
		free(tmp);
	}
	map[i] = NULL;
	return (aligne_map(map));
}


int 	find_max_height(char **map)
{
	int i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int 	find_max_width(char **map)
{
	int i;
	int len;
	int max_width;

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



void 	check_map(t_game *game)
{
	char **map;
	int i;
	int j;
	int is_player;

	map = game->map;
	is_player = 0;
	game->map_width = find_max_width(map);
	game->map_height = find_max_height(map);
	i = 0;
	while (map[i]) {
		j = 0;
		while (map[i][j]) {
			if (map[i][j] == '0') {
				if (!check_borders(i, j, map, game))
					error("Wrong map!");
			}
			if (check_begin_pos(map[i][j])) {
				init_start_pos(game, map[i][j], i, j);
				is_player = 1;
			}
			j++;
		}
		i++;
	}
	if (!is_player)
		error("No player on map");
}
