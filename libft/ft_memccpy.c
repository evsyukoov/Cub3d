/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 04:01:29 by ccarl             #+#    #+#             */
/*   Updated: 2020/05/03 12:51:10 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char	*dst_char;
	char	*src_char;
	size_t	i;

	dst_char = (char*)dst;
	src_char = (char*)src;
	i = 0;
	while (*src_char && i < n)
	{
		dst_char[i] = src_char[i];
		if (src_char[i] == (char)c)
			return (dst_char + i + 1);
		i++;
	}
	return (0);
}
