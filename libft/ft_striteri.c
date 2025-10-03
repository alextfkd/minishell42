/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:41:34 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/05/13 10:41:59 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static void	force_crash_undefined(void)
{
	int	*ptr;

	ptr = NULL;
	*ptr = 42;
	return ;
}

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	idx;

	if (s == NULL)
		return ;
	if (f == NULL)
		force_crash_undefined();
	idx = 0;
	while (s[idx] != '\0')
	{
		f(idx, &s[idx]);
		idx++;
	}
	return ;
}
