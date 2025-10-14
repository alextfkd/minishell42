/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:49:21 by htsutsum          #+#    #+#             */
/*   Updated: 2025/05/19 14:59:54 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_handle_string(const char c, va_list ap)
{
	if (c == 'c')
		return (ft_putchar(va_arg(ap, int)));
	if (c == 's')
		return (ft_putstr(va_arg(ap, char *)));
	return (-1);
}

static int	ft_handle_number(const char c, va_list ap)
{
	if (c == 'd' || c == 'i')
		return (ft_putint(va_arg(ap, int)));
	if (c == 'u')
		return (ft_putint(va_arg(ap, unsigned int)));
	if (c == 'x')
		return (ft_puthex(va_arg(ap, unsigned int), LOWER_HEX));
	if (c == 'X')
		return (ft_puthex(va_arg(ap, unsigned int), UPPER_HEX));
	if (c == 'p')
		return (ft_putptr(va_arg(ap, void *)));
	return (-1);
}

static int	ft_handle_format(const char **fmt, va_list ap)
{
	int	res;

	res = -1;
	(*fmt)++;
	if (**fmt == '%')
		return (ft_putchar('%'));
	if (**fmt == '\0')
		return (-1);
	res = ft_handle_string(**fmt, ap);
	if (res == -1)
		res = ft_handle_number(**fmt, ap);
	if (res == -1)
		res = ft_putchar('%');
	return (res);
}

int	ft_printf(const char *fmt, ...)
{
	int		len;
	int		ret;
	va_list	ap;

	if (!fmt || !*fmt)
		return (-1);
	len = 0;
	va_start(ap, fmt);
	while (*fmt)
	{
		if (*fmt == '%')
			ret = ft_handle_format(&fmt, ap);
		else
			ret = ft_putchar(*fmt);
		if (ret < 0)
			return (va_end(ap), -1);
		len += ret;
		fmt++;
	}
	return (va_end(ap), len);
}
