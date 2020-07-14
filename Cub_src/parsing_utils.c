/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 19:39:19 by denis             #+#    #+#             */
/*   Updated: 2020/07/09 18:19:04 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		starts_with(char *start, char *string)
{
	while (*string && *start && *string == *start)
	{
		string++;
		start++;
	}
	if (!(*start))
		return (1);
	return (0);
}

int		digit_len(char *string)
{
	int count;

	count = 0;
	while (*string >= '0' && *string <= '9')
	{
		string++;
		count++;
	}
	return (count);
}

char	*extra_spaces(int len, int max_width)
{
	char	*str;
	int		i;

	str = (char*)malloc(sizeof(char) * (max_width - len + 1));
	i = 0;
	while (len < max_width)
	{
		str[i++] = ' ';
		len++;
	}
	str[i] = '\0';
	return (str);
}

int		skip_spaces(char **string)
{
	while (**string == ' ')
		(*string)++;
	if (ft_isdigit(**string) || **string == ',')
		return (1);
	return (0);
}

void	error(char *message)
{
	ft_putstr_fd(message, 2);
	my_exit();
}
