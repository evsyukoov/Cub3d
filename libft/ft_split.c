/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 18:21:17 by denis             #+#    #+#             */
/*   Updated: 2020/05/04 16:12:15 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

static void		skip(char const **s, char delimetr)
{
	while (**s == delimetr && **s)
		(*s)++;
}

static int		word_len(char const *s, char delimetr)
{
	int len;

	len = 0;
	while (s[len] != delimetr && s[len])
		len++;
	return (len);
}

static int		word_counter(char const *s, char delimetr)
{
	int words;

	words = 0;
	skip(&s, delimetr);
	while (*s)
	{
		while (*s != delimetr && *s)
			s++;
		words++;
		skip(&s, delimetr);
	}
	return (words);
}

char			**ft_split(char const *s, char c)
{
	int		words;
	int		i;
	int		j;
	char	**res;

	if (!s)
		return (0);
	words = word_counter(s, c);
	if (!(res = (char**)malloc(sizeof(char*) * (words + 1))))
		return (NULL);
	i = 0;
	skip(&s, c);
	while (i < words)
	{
		if (!(res[i] = (char*)malloc(sizeof(char) * (word_len(s, c) + 1))))
			return (0);
		j = 0;
		while (*s != c && *s)
			res[i][j++] = *s++;
		res[i][j] = '\0';
		i++;
		skip(&s, c);
	}
	res[i] = NULL;
	return (res);
}
