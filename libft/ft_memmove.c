/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:29:44 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/05/02 09:07:43 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dp;
	unsigned char	*sp;

	if (dst == NULL && src == NULL)
		return (NULL);
	dp = (unsigned char *) dst;
	sp = (unsigned char *) src;
	if ((size_t)dp > (size_t)sp && (size_t)dp < (size_t)sp + len)
	{
		while (len > 0)
		{
			*(dp + len - 1) = *(sp + len - 1);
			len--;
		}
		return (dst);
	}
	else
	{
		while (len--)
			*dp++ = *sp++;
	}
	return (dst);
}
/*
	while (len > 0)
	{
		*dp++ = *sp++;
		len--;
	}
	return (dst);
#include <stdio.h>

int main ()
{
	char dst[] = "abcdef";
	char src[] = "123456";
	printf("init -> %s\n", dst);
	ft_memmove(dst, dst+1, 5);
	printf("end -> %s\n", dst);
	return (0);
}
*/
