/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:48:41 by htsutsum          #+#    #+#             */
/*   Updated: 2025/05/18 20:46:09 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putint(long long nb)
{
	char	*s;
	int		len;

	s = ft_lltoa(nb);
	if (!s)
		return (-1);
	len = ft_putstr(s);
	free(s);
	return (len);
}
