/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:19:25 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/05/08 19:26:35 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
The  strdup()  function  returns  a pointer to a new string which is
a duplicate of the string s. Memory for the new string is obtained
with malloc(3), and can be freed with free(3).
*/
char	*ft_strdup(const char *s)
{
	int			len;
	char		*arr;

	len = ft_strlen(s);
	arr = (char *)ft_calloc(len + 1, sizeof(char));
	if (arr == NULL)
		return (NULL);
	ft_strlcpy(arr, s, len + 1);
	return (arr);
}
