/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchrr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 14:16:12 by denis             #+#    #+#             */
/*   Updated: 2020/04/30 14:17:32 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *str, int ch)
{
	int len;

	len = ft_strlen(str);
	str += len;
	while (len && *str != ch)
	{
		str--;
		len--;
	}
	if (*str == ch)
		return ((char*)str);
	return (0);
}
