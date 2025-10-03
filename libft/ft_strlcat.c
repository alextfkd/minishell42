/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:34:44 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/05/08 15:43:53 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(
	char *restrict dst,
	const char *restrict src,
	size_t dst_buf_size)
{
	size_t	dst_size;
	size_t	src_size;
	size_t	src_idx;

	dst_size = ft_strlen(dst);
	src_size = ft_strlen(src);
	src_idx = 0;
	if (dst_buf_size < dst_size)
		return (dst_buf_size + src_size);
	if (dst_size + src_size + 1 < dst_buf_size)
	{
		dst += dst_size;
		while (*src)
			*dst++ = *src++;
		*dst = '\0';
		return (dst_size + src_size);
	}
	dst += dst_size;
	while (dst_size + src_idx + 1 < dst_buf_size)
	{
		dst[src_idx] = src[src_idx];
		src_idx++;
	}
	dst[src_idx] = '\0';
	return (dst_size + src_size);
}
