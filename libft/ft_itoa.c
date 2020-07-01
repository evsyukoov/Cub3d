/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 18:31:39 by denis             #+#    #+#             */
/*   Updated: 2020/05/04 16:14:51 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int		ft_size(int n)
{
	int		i;

	i = 0;
	if (n < 0)
	{
		if (n == -2147483648)
		{
			i++;
			n = -147483648;
		}
		n = -n;
		i++;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		size;
	char	*res;

	size = ft_size(n);
	if (!(res = (char*)malloc(sizeof(char) * (size + 1))))
		return (0);
	if (n == 0)
		res[0] = '0';
	if (n < 0)
	{
		if (n == -2147483648)
		{
			res[1] = '2';
			n = -147483648;
		}
		res[0] = '-';
		n = -n;
	}
	res[size] = '\0';
	while (n > 0)
	{
		res[--size] = n % 10 + '0';
		n /= 10;
	}
	return (res);
}
