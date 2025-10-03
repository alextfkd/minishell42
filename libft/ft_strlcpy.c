/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:17:07 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/05/09 12:09:39 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstSize)
{
	size_t	srclen;
	char	*dstp;

	srclen = ft_strlen(src);
	dstp = dst;
	if (dstSize == 0)
		return (srclen);
	if (srclen <= dstSize - 1)
	{
		while (*src)
			*dstp++ = *src++;
		*dstp = '\0';
		return (srclen);
	}
	while (dstSize > 1)
	{
		*dstp++ = *src++;
		dstSize--;
	}
	*dstp = '\0';
	return (srclen);
}
