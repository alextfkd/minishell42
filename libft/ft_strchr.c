/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:35:17 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/05/08 17:57:38 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
The strchr() function returns a pointer to the first occurrence of the
character c in the string s.
*/
char	*ft_strchr(const char *s, int c)
{
	unsigned char	*us;
	unsigned char	uc;

	us = (unsigned char *)s;
	uc = (unsigned char )c;
	while (*us)
	{
		if (*us == uc)
			return ((char *)us);
		us++;
	}
	if (*us == uc)
		return ((char *)us);
	return (NULL);
}
