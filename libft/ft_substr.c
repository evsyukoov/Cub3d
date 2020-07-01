/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 14:59:31 by denis             #+#    #+#             */
/*   Updated: 2020/05/04 17:11:28 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	mem_size;

	mem_size = len;
	i = 0;
	if (!s)
		return (0);
	if (ft_strlen(s) <= start)
	{
		mem_size = 0;
		s += ft_strlen(s);
	}
	else
	{
		s += start;
		if (ft_strlen(s) < len)
			mem_size = ft_strlen(s);
	}
	if (!(res = (char*)malloc(sizeof(char) * (mem_size + 1))))
		return (0);
	while (i < len && *s)
		res[i++] = *s++;
	res[i] = '\0';
	return (res);
}
