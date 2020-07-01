/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 15:07:51 by denis             #+#    #+#             */
/*   Updated: 2020/05/04 16:18:01 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int		is_contains(char to_find, char const *set)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (set[i] == to_find)
			return (1);
		i++;
	}
	return (0);
}

size_t	trimmed_len(char const *start, char const *end)
{
	size_t	len;

	len = 0;
	while (start != end)
	{
		start++;
		len++;
	}
	return (len);
}

char	*ft_strtrim(char const *s, char const *set)
{
	char		*newstr;
	const char	*endptr;
	int			i;
	int			len;

	if (!s)
		return (0);
	while (*s && is_contains(*s, set))
		s++;
	len = ft_strlen(s);
	while (is_contains(s[len - 1], set) && len)
		len--;
	if (!(newstr = (char*)malloc(sizeof(char) * (len + 1))))
		return (0);
	i = 0;
	endptr = s + len;
	while (s != endptr)
		newstr[i++] = *s++;
	newstr[i] = '\0';
	return (newstr);
}
