/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:05:02 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/14 23:38:08 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthex(unsigned int nb, int flag)
{
	char	*s;
	int		len;

	s = ft_htoa((unsigned long long)nb, flag);
	if (!s)
		return (-1);
	len = 0;
	len = ft_putstr(s);
	free(s);
	return (len);
}
