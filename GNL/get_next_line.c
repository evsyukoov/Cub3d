/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 19:00:30 by denis             #+#    #+#             */
/*   Updated: 2020/05/15 16:00:52 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*allocate_new(char *balance, int pos)
{
	char	*new_balance;
	int		i;

	balance += pos;
	i = 0;
	if (!(new_balance = (char*)malloc(sizeof(char) * (ft_strlen(balance) + 1))))
		return (0);
	while (*balance)
		new_balance[i++] = *balance++;
	new_balance[i] = '\0';
	return (new_balance);
}

char	*allocate_empty_line(char *line)
{
	line = (char*)malloc(sizeof(char) * 1);
	*line = '\0';
	return (line);
}

char	*init_line(char *s2)
{
	char	*res;
	int		i;

	i = 0;
	if (!(res = (char*)malloc(sizeof(char) * (ft_strlen(s2) + 1))))
		return (0);
	while (*s2 && *s2 != '\n')
		res[i++] = *s2++;
	res[i] = '\0';
	return (res);
}

int		get_next_line(int fd, char **line)
{
	int			count;
	char		buff[BUFFER_SIZE + 1];
	static char	*balance;
	int			flag;

	flag = 0;
	*line = check_balance(&balance, *line, &flag);
	if (fd < 0 || !line || flag == -1 || BUFFER_SIZE < 1)
		return (-1);
	if (flag == 1)
		return (1);
	while ((count = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[count] = '\0';
		if (!(*line = ft_strjoin_gnl(*line, buff)))
			return (-1);
		if (find_pos(buff))
			return (init_balance(buff, find_pos(buff), &balance));
	}
	balance = NULL;
	if (!(*line))
		*line = allocate_empty_line(*line);
	if (count < 0)
		return (-1);
	return (0);
}
