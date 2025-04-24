/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_with_set.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:44:44 by rguigneb          #+#    #+#             */
/*   Updated: 2025/04/24 11:51:24 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static size_t	get_next_set_occurency1(char const *s, char *set)
{
	size_t	i;

	i = 0;
	while (s && s[i] && !ft_strchr(set, s[i]))
		i++;
	return (i);
}

static size_t	get_word_count1(char const *s, char *set)
{
	size_t	i;
	size_t	is_in_word;
	size_t	count;

	i = -1;
	is_in_word = 0;
	count = 0;
	while (s[++i])
	{
		if (ft_strchr(set, s[i]))
			is_in_word = 0;
		else if (is_in_word++ == 0)
			count++;
	}
	return (count);
}

char	**ft_split_with_set(char const *s, char *set)
{
	size_t	i;
	size_t	total_len;
	size_t	next_char_index;
	char	**tab;

	i = 0;
	total_len = get_word_count1(s, set) * sizeof(char *) + sizeof(NULL);
	tab = (char **)safe_malloc(total_len);
	if (!tab)
		return (NULL);
	while (*s)
	{
		if (ft_strchr(set, *s))
			s++;
		else
		{
			next_char_index = get_next_set_occurency1(s, set);
			tab[i++] = ft_substr(s, 0, next_char_index);
			s += next_char_index;
		}
	}
	tab[i] = NULL;
	return (tab);
}
