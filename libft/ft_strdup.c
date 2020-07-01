/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 13:54:41 by denis             #+#    #+#             */
/*   Updated: 2020/04/30 13:55:32 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*res;
	int		i;

	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	i = 0;
	if (!res)
		return (0);
	while (*str)
		res[i++] = *str++;
	res[i] = '\0';
	return (res);
}
