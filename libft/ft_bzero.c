/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:29:12 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/05/08 16:49:11 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
The bzero() function erases the data in the n bytes of the memory
starting at the location pointed to by s,
by writing zeros (bytes containing '\0') to that area.
*/
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, (unsigned char)0, n);
}
/*
#include <stdio.h>

int main()
{
	char s[] = "abcdefg";
	int i = 0;
	while (i < 7)
	{
		printf("%c", s[i]);
		i++;
	}
	i = 0;
	ft_bzero(s, 5);
	while (i < 7)
	{
		printf("%c", s[i]);
		i++;
	}
	return (1);
}
*/
