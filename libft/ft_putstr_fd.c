/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:41:29 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/05/13 10:13:06 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static void	force_crash_invalid_fd(void)
{
	int	*ptr;

	ptr = NULL;
	*ptr = 42;
	return ;
}

void	ft_putstr_fd(char *s, int fd)
{
	int	slen;

	slen = write(fd, s, ft_strlen(s));
	if (slen == -1)
	{
		write(2, "Error! ft_putstr_fd() failed: Invalid fd.\n", 42);
		force_crash_invalid_fd();
	}
	return ;
}
