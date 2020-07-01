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

int 	starts_with(char *start, char *string)
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

int 	digit_len(char *string)
{
	int count;

	count = 0;
	while (*string >= '0' && *string <= '9') {
		string++;
		count++;
	}
	return (count);
}

int 	next_comma(char **string)
{
	while (**string && **string != ',')
		(*string)++;
	if (**string == ',') {
		(*string)++;
		return (1);
	}
	return (0);
}

int 	skip_spaces(char **string)
{
	while (**string == ' ')
		(*string)++;
	if (ft_isdigit(**string) || **string == ',')
		return (1);
	return (0);
}

