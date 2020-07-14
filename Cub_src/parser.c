/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 19:39:19 by denis             #+#    #+#             */
/*   Updated: 2020/07/11 14:53:29 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_list	*reader(int fd)
{
	t_list	*lst;
	t_list	*node;
	char	*line;

	lst = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (!(node = ft_lstnew(line)))
			error("Malloc error!");
		ft_lstadd_back(&lst, node);
	}
	if (!(node = ft_lstnew(line)))
		error("Malloc error!");
	ft_lstadd_back(&lst, node);
	return (lst);
}

void	init_resolution(t_game *game, char *string)
{
	int			resolution[2];
	int			i;
	static int	k;

	i = 0;
	string += 1;
	if (++k > 1)
		error("Dublicate resolution argument");
	if (*string != ' ')
		error("No or wrong separator!");
	while (i < 2)
	{
		skip_spaces(&string);
		resolution[i++] = ft_atoi(string);
		string += digit_len(string);
	}
	skip_spaces(&string);
	if (resolution[0] <= 0 || resolution[1] <= 0 || *string)
		error("Wrong screen resolution string");
	if (resolution[0] > MONITORX)
		resolution[0] = MONITORX;
	if (resolution[1] > MONITORY)
		resolution[1] = MONITORY;
	game->win_height = resolution[1];
	game->win_width = resolution[0];
}

int		parse_color(char *string)
{
	static int	k;
	int			rgb[3];
	int			i;

	if (*(++string) != ' ')
		error("No or wrong separator!");
	i = 0;
	if (++k > 2)
		error("Wrong color arguments!\n");
	while (i < 3)
	{
		while (*string == ' ')
			string++;
		if (!ft_isdigit(*string))
			error("Wrong color string");
		if ((rgb[i++] = ft_atoi(string)) > 255)
			error("Wrong color. Color channel must be in 0 to 255");
		string += digit_len(string);
		while (*string == ' ' && *string)
			string++;
		if (*string != ',' && *string != '\0')
			error("Wrong color string");
		string++;
	}
	return (rgb_to_int(rgb[0], rgb[1], rgb[2]));
}

void	load_textures(t_game *game, char *str, t_texture **text)
{
	int		i;
	char	*path;

	i = get_texture_index(str, &path);
	skip_spaces(&path);
	text[i]->img = mlx_xpm_file_to_image(game->mlx, path,
	&(text[i]->width), &(text[i]->height));
	if (!text[i]->img)
		error("Wrong texture string!");
	text[i]->addr = mlx_get_data_addr(text[i]->img,
	&(text[i]->bits_per_pixel), &(text[i]->line_length), &(text[i]->endian));
}

int		parse_config(t_list *lst, t_game *game)
{
	t_list *tmp;

	while (lst)
	{
		tmp = lst;
		if (starts_with("R", lst->content))
			init_resolution(game, (char*)lst->content);
		else if (starts_with("F", lst->content))
			game->floor_color = parse_color((char*)lst->content);
		else if (starts_with("C", lst->content))
			game->ceiling_color = parse_color((char*)lst->content);
		else if (is_starts_with_text((char*)lst->content))
			load_textures(game, (char*)lst->content, game->textures);
		else if (*(char*)(lst->content) != '\0')
		{
			parse_remainder(game, lst);
			break ;
		}
		free(lst->content);
		lst = lst->next;
		free(tmp);
	}
	return (1);
}
