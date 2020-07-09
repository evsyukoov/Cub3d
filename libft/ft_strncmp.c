/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 14:08:16 by denis             #+#    #+#             */
/*   Updated: 2020/05/02 14:34:53 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *str1, const char *str2, size_t len)
{
	size_t	i;

	i = 0;
	while (*str1 && *str2 && *str1 == *str2 && i < len - 1)
	{
		str1++;
		str2++;
		i++;
	}
	return ((unsigned char)*str1 - (unsigned char)*str2);
}
