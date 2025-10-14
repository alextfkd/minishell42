/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:04:15 by htsutsum          #+#    #+#             */
/*   Updated: 2025/05/06 11:11:36 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	if (n == 0)
		return (dest);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (s < d)
	{
		while (n--)
		{
			d[n] = s[n];
		}
	}
	else
		return (ft_memcpy(d, s, n));
	return (d);
}

// int main(void)
// {

// 	char buf1[] = "ABCDEFG";
// 	char buf2[] = "ABCDEFG";

// 	//bufの先頭から3バイト進めた位置にbufの先頭から3バイトコピー
// 	ft_memmove(buf1+3,buf1,3);
// 	printf("コピー後のbuf文字列→%s\n",buf1);
// 	// ABCABCFG

// 	ft_memmove(buf2,buf2+3,3);
// 	printf("コピー後のbuf文字列→%s\n",buf2);
// 	// DEFDEFG
// 	return (0);
// }