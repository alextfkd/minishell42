/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:41:43 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/05/13 10:23:34 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	min(size_t a, size_t b)
{
	if (a >= b)
		return (b);
	return (a);
}

static void	force_crash_undefined(void)
{
	int	*ptr;

	ptr = NULL;
	*ptr = 42;
	return ;
}

/*
Allocates memory (using malloc(3)) and returns a substring from the string ’s’.
The substring starts at index ’start’ and has a maximum length of ’len’.
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	slen;
	size_t	mlen;
	char	*subs;

	if (s == NULL)
		force_crash_undefined();
	slen = ft_strlen(s);
	s += start;
	if (start >= slen)
		return (ft_calloc(1, sizeof(char)));
	mlen = min(len, slen - start);
	subs = (char *)ft_calloc(mlen + 1, sizeof(char));
	if (subs == NULL)
		return (NULL);
	ft_strlcpy(subs, s, mlen + 1);
	return (subs);
}
/*
int main(void)
{
	const char *s = "abcdefghi";
	printf("%s\n", ft_substr(s, 3, 3));
	printf("%s\n", ft_substr(s, 3, 6));
	printf("%s\n", ft_substr(s, 3, 9));
	printf("%s\n", ft_substr(s, 12, 9));
}
*/
