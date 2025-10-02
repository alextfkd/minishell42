/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:06:09 by htsutsum          #+#    #+#             */
/*   Updated: 2025/05/18 20:46:06 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putptr(void *p)
{
	int					len;
	unsigned long long	nb;
	char				*s;

	if (!p)
		return (ft_putstr("(nil)"));
	len = ft_putstr("0x");
	if (len < 0)
		return (-1);
	nb = (unsigned long long)p;
	s = ft_htoa(nb, LOWER_HEX);
	len += ft_putstr(s);
	free(s);
	return (len);
}
