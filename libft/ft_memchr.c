/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:35:11 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/04/28 12:10:06 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*us;
	unsigned char	uc;
	size_t			i;

	us = (unsigned char *)s;
	uc = (unsigned char)c;
	i = 0;
	while (i++ < n)
	{
		if (*us == uc)
			return ((void *)us);
		us++;
	}
	return (NULL);
}
