/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 19:00:16 by denis             #+#    #+#             */
/*   Updated: 2020/05/15 16:01:25 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*res;
	int		len;
	int		i;
	char	*tmp;

	i = 0;
	tmp = s1;
	if (!s2)
		return (0);
	if (!s1)
	{
		if (!(res = init_line(s2)))
			return (0);
		return (res);
	}
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(res = (char*)malloc(sizeof(char) * (len + 1))))
		return (0);
	while (*s1 && *s1 != '\n')
		res[i++] = *s1++;
	while (*s2 && *s2 != '\n')
		res[i++] = *s2++;
	res[i] = '\0';
	free(tmp);
	return (res);
}

int		find_pos(char *buff)
{
	int i;
	int pos;

	i = 0;
	pos = 0;
	while (buff[i])
	{
		if (buff[i] == '\n')
		{
			pos = i + 1;
			return (pos);
		}
		i++;
	}
	return (0);
}

int		init_balance(char *buff, int pos, char **balance)
{
	int len;
	int	i;

	buff += pos;
	i = 0;
	len = ft_strlen(buff);
	if (!((*balance) = (char*)malloc(sizeof(char) * (len + 1))))
		return (-1);
	while (*buff)
		(*balance)[i++] = *buff++;
	(*balance)[i] = '\0';
	return (1);
}

char	*check_balance(char **balance, char *line, int *flag)
{
	int		pos;
	char	*tmp;

	line = NULL;
	if (*balance)
	{
		tmp = *balance;
		pos = find_pos(*balance);
		if (!(line = ft_strjoin_gnl(line, *balance)))
		{
			*flag = -1;
			free(tmp);
			return (0);
		}
		if (pos)
		{
			if (!((*balance) = allocate_new(*balance, pos)))
				*flag = -1;
			*flag = 1;
		}
		free(tmp);
		return (line);
	}
	return (0);
}
