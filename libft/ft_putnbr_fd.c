/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:41:26 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/05/13 10:11:11 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include "libft.h"

static void	putstr_and_return(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	return ;
}

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == INT_MIN)
		return (putstr_and_return("-2147483648", fd));
	if (n == 0)
		return (putstr_and_return("0", fd));
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n / 10 != 0)
		ft_putnbr_fd(n / 10, fd);
	c = n % 10 + '0';
	ft_putchar_fd(c, fd);
}
