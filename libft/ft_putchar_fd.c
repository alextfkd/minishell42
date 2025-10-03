/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:41:18 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/05/13 10:09:49 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	force_crash_invalid_fd(void)
{
	int	*ptr;

	ptr = NULL;
	*ptr = 42;
	return ;
}

void	ft_putchar_fd(char c, int fd)
{
	int	wlen;

	wlen = write(fd, &c, 1);
	if (wlen == -1)
	{
		write(2, "Error! ft_putchar_fd() failed: Invalid fd.\n", 43);
		force_crash_invalid_fd();
	}
	return ;
}
