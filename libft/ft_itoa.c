/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:40:08 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/05/08 20:12:02 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	digit2chr(long n)
{
	char	map[10];

	map[0] = '0';
	map[1] = '1';
	map[2] = '2';
	map[3] = '3';
	map[4] = '4';
	map[5] = '5';
	map[6] = '6';
	map[7] = '7';
	map[8] = '8';
	map[9] = '9';
	return (map[n]);
}

static int	get_digits(int n)
{
	int		digit;
	long	ln;

	if (n == 0)
		return (1);
	digit = 1;
	ln = (long) n;
	if (ln < 0)
	{
		ln *= -1;
		digit++;
	}
	while (ln / 10 > 0)
	{
		digit++;
		ln = ln / 10;
	}
	return (digit);
}

char	*ft_itoa(int n)
{
	int		a_len;
	long	ln;
	char	*arr;

	a_len = get_digits(n);
	arr = (char *)malloc(sizeof(char) * (a_len + 1));
	if (arr == NULL)
		return (NULL);
	ln = (long)n;
	if (n < 0)
	{
		arr[0] = '-';
		ln *= -1;
	}
	arr[a_len--] = '\0';
	if (ln == 0)
		arr[0] = '0';
	while (ln != 0)
	{
		arr[a_len--] = digit2chr(ln % 10);
		ln = ln / 10;
	}
	return (arr);
}
/*
int	main(void)
{
	printf("%s\n", ft_itoa(0));
	printf("%s\n", ft_itoa(123));
	printf("%s\n", ft_itoa(-123));
}
*/