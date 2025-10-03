/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:36:29 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/04/28 11:36:49 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

static size_t	filled_size_t(unsigned char uc)
{
	size_t	res;
	size_t	i;

	res = 0;
	i = 0;
	while (i < sizeof(size_t))
	{
		res = res << 8 | uc;
		i++;
	}
	return (res);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*dp;
	unsigned char	uc;
	size_t			fill;
	size_t			*stp;

	stp = (size_t *)b;
	uc = (unsigned char)c;
	fill = filled_size_t(uc);
	while (len >= sizeof(size_t))
	{
		*stp++ = fill;
		len = len - sizeof(size_t);
	}
	dp = (unsigned char *)stp;
	while (len-- > 0)
		*dp++ = uc;
	return (b);
}
