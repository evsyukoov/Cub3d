/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 14:27:15 by denis             #+#    #+#             */
/*   Updated: 2020/05/03 12:50:30 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *arr1, const void *arr2, size_t n)
{
	unsigned char	*char_arr1;
	unsigned char	*char_arr2;
	size_t			i;

	char_arr1 = (unsigned char*)arr1;
	char_arr2 = (unsigned char*)arr2;
	i = 0;
	while (i < n && *char_arr1 == *char_arr2)
	{
		i++;
		char_arr1++;
		char_arr2++;
	}
	if (i == n)
		return (0);
	return (*char_arr1 - *char_arr2);
}
