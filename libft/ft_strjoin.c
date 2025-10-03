/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:41:37 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/05/08 18:14:49 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*arr;
	size_t	i;

	arr = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (*s1)
		arr[i++] = *s1++;
	while (*s2)
		arr[i++] = *s2++;
	return (arr);
}
/*
int main(void)
{
	char const s1[] = "abc";
	char const s2[] = "def";

	if (strcmp("abcdef", ft_strjoin(s1, s2)) == 0)
		printf("PASS, s1: '%s', s2: '%s'\n", s1, s2);
	else
		printf("FAIL, s1: '%s', s2: '%s'\n", s1, s2);

	char const s3[] = "";
	char const s4[] = "def";

	if (strcmp("def", ft_strjoin(s3, s4)) == 0)
		printf("PASS, s3: '%s', s4: '%s'\n", s3, s4);
	else
		printf("FAIL, s3: '%s', s4: '%s'\n", s3, s4);
	return (0);
}
*/
