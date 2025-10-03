/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:25:44 by htsutsum          #+#    #+#             */
/*   Updated: 2025/07/31 17:16:44 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define UPPER_HEX 1
# define LOWER_HEX 0
# include "libft.h"
# include <stdarg.h>

int		ft_printf(const char *fmt, ...);
char	*ft_htoa(unsigned long long nb, int flag);
char	*ft_lltoa(long long nb);
int		ft_putchar(char c);
int		ft_putstr(char *s);
int		ft_putptr(void *p);
int		ft_putstr(char *s);
int		ft_putint(long long nb);
int		ft_puthex(unsigned int nb, int flag);

#endif
