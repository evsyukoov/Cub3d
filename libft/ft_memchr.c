/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 14:24:16 by denis             #+#    #+#             */
/*   Updated: 2020/04/30 18:54:52 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *arr, int c, size_t n)
{
	size_t	i;
	char	*char_arr;

	i = 0;
	char_arr = (char*)arr;
	while (i < n)
	{
		if (char_arr[i] == c)
			return (&char_arr[i]);
		i++;
	}
	return (0);
}
