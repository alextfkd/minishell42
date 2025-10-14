/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 20:51:06 by htsutsum          #+#    #+#             */
/*   Updated: 2025/08/03 09:53:22 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	decimal_point(char *str, double *nbr, double *power, int *i)
{
	if (str[*i] == '.')
	{
		(*i)++;
		while (str[*i] && ft_isdigit(str[*i]))
		{
			*nbr = *nbr * 10.0 + (str[*i] - '0');
			*power *= 10.0;
			(*i)++;
		}
	}
}

double	ft_atof(char *str)
{
	double	nbr;
	double	sign;
	double	power;
	int		i;

	nbr = 0;
	sign = 1;
	i = 0;
	power = 1.0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		nbr = nbr * 10.0 + (str[i] - '0');
		i++;
	}
	decimal_point(str, &nbr, &power, &i);
	return ((nbr / power) * sign);
}
