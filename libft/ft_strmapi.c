/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 18:40:17 by denis             #+#    #+#             */
/*   Updated: 2020/05/02 17:10:49 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new_str;
	int		i;

	if (!s || !f)
		return (0);
	new_str = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!new_str)
		return (0);
	i = 0;
	while (*s)
	{
		new_str[i] = f(i, *s);
		s++;
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
