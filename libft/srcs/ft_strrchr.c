/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:58:48 by htsutsum          #+#    #+#             */
/*   Updated: 2025/05/03 12:06:25 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char		*end;
	unsigned char	uc;

	uc = (unsigned char)c;
	end = NULL;
	while (*s != '\0')
	{
		if (*s == (char)uc)
			end = s;
		s++;
	}
	if ((char)uc == *s)
		return ((char *)s);
	return ((char *)end);
}
