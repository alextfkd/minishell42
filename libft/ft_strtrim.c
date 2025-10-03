/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:41:46 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/05/13 10:27:31 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_inset(char const c, char const *set)
{
	while (*set)
	{
		if (c == *set++)
			return (1);
	}
	return (0);
}

static void	force_crash_undefined(void)
{
	int	*ptr;

	ptr = NULL;
	*ptr = 42;
	return ;
}

/*
Allocates memory (using malloc(3)) and
returns a copy of ’s1’ with characters from ’set’ removed
from the beginning and the end.
*/
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		len;
	const char	*pstr;
	const char	*pend;
	char		*arr;

	if (s1 == NULL)
		force_crash_undefined();
	len = ft_strlen(s1);
	pstr = s1;
	pend = s1 + len - 1;
	while (is_inset(*pstr, set) != 0)
		pstr++;
	while (is_inset(*pend, set) != 0 && *pstr != '\0')
		pend--;
	arr = ft_substr(pstr, 0, pend - pstr + 1);
	return (arr);
}
/*
Parameters
s1: The string to be trimmed.
set: The string containing the set of characters to be removed.

Return value
The trimmed string.  NULL if the allocation fails.

External functs. malloc

Description
*/
