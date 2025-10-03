/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:35:36 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/05/08 17:59:17 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
The strrchr() function returns a pointer to the last occurrence of
the character c in the string s.
*/
char	*ft_strrchr(const char *s, int c)
{
	unsigned char	*u_start;
	unsigned char	*u_ptr;
	unsigned char	uc;

	u_start = (unsigned char *)s;
	u_ptr = (unsigned char *)s;
	uc = (unsigned char)c;
	while (*u_ptr != '\0')
		u_ptr++;
	while (u_ptr > u_start)
	{
		if (*u_ptr == uc)
			return ((char *)u_ptr);
		u_ptr--;
	}
	if (*u_ptr == uc)
		return ((char *)u_ptr);
	return (NULL);
}
