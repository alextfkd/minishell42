/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:32:58 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/05/01 13:30:53 by tkatsuma         ###   ########.fr       */
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

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*uc1;
	const unsigned char	*uc2;
	int					res;

	if (s1 == NULL || s2 == NULL)
		force_crash_undefined();
	uc1 = (const unsigned char *)s1;
	uc2 = (const unsigned char *)s2;
	res = 0;
	while (n > 0)
	{
		if (*uc1 - *uc2 != 0)
			return (*uc1 - *uc2);
		uc1++;
		uc2++;
		n--;
	}
	return (res);
}
/*
#include <stdio.h>

int main()
{
	char s1[] = "abc";
	char s2[] = "abc";
	printf("ft s1: %s, s2: %s -> %d\n", s1, s2, ft_memcmp(s1, s2, sizeof(s1)));
	printf("ori s1: %s, s2: %s -> %d\n", s1, s2, memcmp(s1, s2, sizeof(s1)));

	char s3[] = "ab";
	char s4[] = "abc";
	printf("ft s3: %s, s4: %s -> %d\n", s3, s4, ft_memcmp(s3, s4, sizeof(s3)));
	printf("ori s3: %s, s4: %s -> %d\n", s3, s4, memcmp(s3, s4, sizeof(s4)));
}

NAME
	memcmp – compare byte string

		LIBRARY
			Standard C Library(libc, -lc)

				SYNOPSIS
#include <string.h>

	int memcmp(const void *s1, const void *s2, size_t n);

DESCRIPTION
	 The memcmp() function compares byte string s1 against byte string s2.
	 Both strings are assumed to be n bytes long.

RETURN VALUES
	 The memcmp() function returns zero if the two strings are identical,
	 otherwise returns the difference between the first two differing bytes
	 (treated as unsigned char values, so that ‘\200’ is
	 greater than ‘\0’, for example).
	 Zero-length strings are always identical.
	 This behavior is not required by C and portable code
	 should only depend on the sign of the returned value.
*/
