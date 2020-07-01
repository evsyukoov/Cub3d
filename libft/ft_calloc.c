/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 16:08:02 by denis             #+#    #+#             */
/*   Updated: 2020/05/02 15:31:05 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t number, size_t size)
{
	void *ptr;

	ptr = malloc(number * size);
	if (!ptr)
		return (0);
	ft_memset(ptr, 0, number * size);
	return (ptr);
}
