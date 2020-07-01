/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 20:13:51 by denis             #+#    #+#             */
/*   Updated: 2020/05/05 11:11:25 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

static int	check_overlap(const char *str, int sign)
{
	long overlap;
	long prev;

	overlap = 0;
	while ('0' <= *str && *str <= '9')
	{
		prev = overlap;
		overlap = overlap * 10 + (*str - '0');
		if (prev > overlap && sign == -1)
			return (0);
		if (prev > overlap && sign == 1)
			return (-1);
		str++;
	}
	return (1);
}

int			ft_atoi(const char *str)
{
	int sign;
	int res;
	int i;

	sign = 1;
	res = 0;
	i = 0;
	while (*str == '\n' || *str == '\t' || *str == '\r'
	|| *str == '\v' || *str == '\f' || *str == ' ')
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	if (*str == '+' && sign != -1)
		str++;
	while ('0' <= str[i] && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (check_overlap(str, sign) == 1)
		return (res * sign);
	return (check_overlap(str, sign));
}
