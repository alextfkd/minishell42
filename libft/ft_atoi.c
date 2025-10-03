/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:42:26 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/05/12 15:14:25 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Checks  for white-space characters.
The white-space characters include space, form-feed ('\f'), newline ('\n'),
carriage return ('\r'), horizontal tab ('\t'), and vertical tab ('\v').
Returns 1 if True, 0 if False.
*/
static int	ft_isspace(char c)
{
	if (c == ' '
		|| c == '\t'
		|| c == '\r'
		|| c == '\n'
		|| c == '\f'
		|| c == '\v'
	)
		return (1);
	return (0);
}

/*
Converts the initial portion of the string pointed to by nptr to int.
'-' -> negative int, '+' -> positive int, '--' -> 0.
*/
int	ft_atoi(const char *nptr)
{
	long	res;
	long	sign;

	res = 0;
	sign = 1;
	while (ft_isspace(*nptr) != 0)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	while (ft_isdigit(*nptr) != 0)
	{
		res = 10 * res + (*nptr - '0');
		nptr++;
	}
	return ((int)(res * sign));
}
