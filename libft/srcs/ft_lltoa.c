/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:57:34 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/14 23:37:46 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	count_ll_len(long long n)
{
	unsigned int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	handel_negative(char *s, long long *nb)
{
	if (*nb < 0)
	{
		s[0] = '-';
		*nb = -*nb;
	}
}

char	*ft_lltoa(long long nb)
{
	unsigned int	len;
	char			*s;

	len = count_ll_len(nb);
	s = (char *)malloc((len + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	s[len--] = '\0';
	if (nb == 0)
		return (s[0] = '0', s);
	handel_negative(s, &nb);
	while (nb > 0)
	{
		s[len] = (nb % 10) + '0';
		nb /= 10;
		len--;
	}
	return (s);
}
