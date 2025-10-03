/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:42:57 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/05/08 18:06:05 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) return (1);
else return (0);
*/
int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/*
#include <ctype.h>
#include <stdio.h>

int main()
{
	int i = 0;
	while (i < 1128)
	{
		printf("{%d}", i);
		if (ft_isalpha(i) != 0 && isalpha(i) != 0)
		{
			printf("fail: int[%d] char[%c]\n", i, (char)i);
			printf("ft -> [%d]\n", ft_isalpha(i));
			printf("original -> [%d]\n", isalpha(i));
			printf("\n");
		}
		else
		{
			//printf("pass: int[%d] char[%c]\n", i, (char)i);
			//printf("ft -> [%d]\n", ft_isalpha(i));
			//printf("original -> [%d]\n", isalpha(i));
			printf("\n");
		}
		i++;
	}
	printf("pass");
}
*/
