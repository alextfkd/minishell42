/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:08:37 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/15 00:34:59 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_hex_len(unsigned long long nb)
{
	int	len;

	len = 0;
	if (!nb)
		return (1);
	while (nb)
	{
		nb >>= 4;
		len++;
	}
	return (len);
}

char	*ft_htoa(unsigned long long nb, int flag)
{
	int				len;
	char			*s;
	unsigned int	tmp;

	len = count_hex_len(nb);
	s = (char *)malloc((len + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	s[len--] = '\0';
	if (!nb)
		return (s[0] = '0', s);
	while (nb > 0)
	{
		tmp = nb & 0xF;
		if (tmp < 10)
			s[len] = tmp + '0';
		else if (flag == UPPER_HEX)
			s[len] = tmp - 10 + 'A';
		else
			s[len] = tmp - 10 + 'a';
		nb >>= 4;
		len--;
	}
	return (s);
}
