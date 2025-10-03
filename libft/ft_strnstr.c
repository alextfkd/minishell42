/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:42:37 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/05/08 19:26:35 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	force_crash_undefined(void)
{
	int	*ptr;

	ptr = NULL;
	*ptr = 42;
	return ;
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	blen;
	size_t	llen;
	size_t	idx;

	if (big == NULL)
		force_crash_undefined();
	blen = ft_strlen(big);
	llen = ft_strlen(little);
	if (llen == 0)
		return ((char *) big);
	if (blen < llen || len < llen)
		return (NULL);
	idx = 0;
	while (idx < len && idx + llen <= len)
	{
		if (ft_strncmp(big, little, llen) == 0)
			return ((char *) big);
		big++;
		idx++;
	}
	return (NULL);
}
/*

int test_strnstr(
	char* (*ft_func)(const char *, const char *, size_t),
	const char *large,
	const char *little,
	size_t len,
	char* ans
)
{
	char *ptr;

	ptr = ft_func(large, little, len);
	if (ptr == NULL && ans == NULL)
	{
		printf("PASS: large (%s) little (%s) len (%zu)
		 -> NULL == NULL\n", large, little, len);
		return (0);
	}
	if (ptr == NULL && ans != NULL)
	{
		printf("FAIL: large (%s) little (%s) len (%zu)
		 -> NULL != %s\n", large, little, len, ans);
		return (0);
	}
	if (ptr != NULL && ans == NULL)
	{
		printf("FAIL: large (%s) little (%s) len (%zu)
		 -> %s != NULL\n", large, little, len, ptr);
		return (0);
	}
	if (strcmp(ptr, ans) != 0)
	{
		printf("FAIL: large (%s) little (%s) len (%zu)
		 -> %s != %s\n", large, little, len, ptr, ans);
		return (1);
	}
	else
	{
		printf("PASS: large (%s) little (%s) len (%zu)
		 -> %s == %s\n", large, little, len, ptr, ans);
		return (0);
	}
}

int main()
{
	const char *large  = "Foo Bar Baz";
	const char *little = "Bar";
	test_strnstr(ft_strnstr, large, little, 0, NULL);
	test_strnstr(ft_strnstr, large, little, 1, NULL);
	test_strnstr(ft_strnstr, large, little, 2, NULL);
	test_strnstr(ft_strnstr, large, little, 3, NULL);
	test_strnstr(ft_strnstr, large, little, 4, NULL);
	test_strnstr(ft_strnstr, large, little, 5, "Bar Baz");
	test_strnstr(ft_strnstr, large, little, 6, "Bar Baz");
	test_strnstr(ft_strnstr, large, little, 7, "Bar Baz");
	test_strnstr(ft_strnstr, large, little, 8, "Bar Baz");
	test_strnstr(ft_strnstr, large, little, 9, "Bar Baz");
	test_strnstr(ft_strnstr, large, little, 10, "Bar Baz");
	return (0);
}
*/
