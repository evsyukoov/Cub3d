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

void	int_to_bytes(int num, unsigned char *header) {
	header[0] = (unsigned char) num;
	header[1] = (unsigned char) (num >> 8);
	header[2] = (unsigned char) (num >> 16);
	header[3] = (unsigned char) (num >> 24);
}

void 	write_header(int fd, t_game *game)
{
	int i;
	unsigned char header[54];
	int filesize;

	i = 0;
	while (i < 54)
		header[i++] = 0;
	header[0] = 'B';
	header[1] = 'M';
	filesize = 54 + game->win_height * game->win_width * 4;
	int_to_bytes(filesize, header + 2);
	header[10] = 54;
	header[14] = 40;
	int_to_bytes(game->win_width , header + 18);
	int_to_bytes(game->win_height * (-1), header + 22);
	header[26] = 1;
	header[28] = 32;
	header[30] = 0;
	int_to_bytes(54 - filesize, header + 34);
	int_to_bytes(game->win_height, header + 38);
	int_to_bytes(game->win_width, header + 42);
	int_to_bytes((int)pow(2, 24), header + 46);
	int_to_bytes(0, header + 50);
	write(fd, header, 54);
}

void 	write_content(int fd, t_game *game)
{
	int i;
	int j;
	unsigned char rgb[4];
	int color;

	i = 0;
	while (i < game->win_height)
	{
		j = 0;
		while (j < game->win_width)
		{
			color = get_color(&game->image, j, i);
			int_to_bytes(color, rgb);
			write(fd, rgb, 4);
			j++;
		}
		i++;
	}
}

void 	create_bmp(t_game *game)
{
	int fd;

	fd = open("./Screenshot/bitmap.bmp",  O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (fd < 0)
		error("Can't create bitmap-file!");
	write_header(fd, game);
	write_content(fd, game);
	close(fd);
}

