/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 13:47:22 by denis             #+#    #+#             */
/*   Updated: 2020/05/01 20:11:16 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *destination, int c, size_t n)
{
	size_t	i;
	char	*buff;

	i = 0;
	buff = (char*)destination;
	while (i < n)
	{
		buff[i] = c;
		i++;
	}
	return (destination);
}
