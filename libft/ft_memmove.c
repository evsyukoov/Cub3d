/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 13:42:44 by denis             #+#    #+#             */
/*   Updated: 2020/05/02 19:21:24 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*dst_char;
	char	*src_char;
	size_t	i;

	if (!dst && !src)
		return (0);
	dst_char = (char*)dst;
	src_char = (char*)src;
	i = 0;
	if (dst_char <= src_char)
		ft_memcpy(dst, src, n);
	else
	{
		i = 1;
		while (i <= n)
		{
			dst_char[n - i] = src_char[n - i];
			i++;
		}
	}
	return (dst);
}
