/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:35:05 by htsutsum          #+#    #+#             */
/*   Updated: 2025/07/23 03:55:08 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_index(char const *s, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			count++;
			in_word = 1;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	**free_split(char **split, size_t n)
{
	while (n--)
		free(split[n]);
	free(split);
	return (NULL);
}

static char	**fill_split(char const *s, char c, char **list, size_t list_len)
{
	long	head;
	size_t	i;
	size_t	j;
	size_t	s_len;

	head = -1;
	i = 0;
	j = 0;
	s_len = ft_strlen(s);
	while (i <= s_len && j < list_len)
	{
		if (s[i] != c && head < 0)
			head = i;
		else if ((s[i] == c || i == s_len) && head >= 0)
		{
			list[j] = ft_substr(s, head, i - head);
			if (!list[j])
				return (free_split(list, j));
			head = -1;
			j++;
		}
		i++;
	}
	return (list[j] = NULL, list);
}

char	**ft_split(char const *s, char c)
{
	size_t	len;
	char	**split;

	if (!s)
		return (NULL);
	len = count_index(s, c);
	split = (char **)malloc((len + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	split = fill_split(s, c, split, len);
	if (!split)
		return (NULL);
	return (split);
}
