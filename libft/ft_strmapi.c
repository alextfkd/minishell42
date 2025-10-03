/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:41:40 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/05/13 10:38:20 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	force_crash_undefined(void)
{
	int	*ptr;

	ptr = NULL;
	*ptr = 42;
	return ;
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	size_t	idx;
	char	*arr;

	if (s == NULL || f == NULL)
		force_crash_undefined();
	len = ft_strlen(s);
	idx = 0;
	arr = (char *)malloc(len + 1);
	if (arr == NULL)
		return (NULL);
	while (idx < len)
	{
		arr[idx] = f(idx, s[idx]);
		idx++;
	}
	arr[len] = '\0';
	return (arr);
}
