/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:37:04 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/05/08 16:03:37 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

static void	force_crash_undefined(void)
{
	int	*ptr;

	ptr = NULL;
	*ptr = 42;
	return ;
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*dp;
	const unsigned char	*sp;

	if (dst == NULL && src == NULL)
		return (NULL);
	if ((size_t)dst < (size_t)src + n && (size_t)src < (size_t)dst + n)
		force_crash_undefined();
	dp = (unsigned char *)dst;
	sp = (const unsigned char *)src;
	while (n > 0)
	{
		*dp++ = *sp++;
		n--;
	}
	return (dst);
}
