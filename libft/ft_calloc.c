/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:59:30 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/05/08 16:53:55 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <stdint.h>

/*
The calloc() function allocates memory for an array of nmemb elements of size
bytes each and returns a pointer to the allocated  memory. The memory is set
to zero.  If nmemb or size is 0, then calloc() returns either NULL,
or a unique pointer value that can later be successfully passed to free().
If the multiplication of nmemb and size would result in integer overflow,
then calloc() returns an error.
*/
void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*arr;

	if (nmemb == 0 || size == 0)
	{
		arr = (unsigned char *)malloc(1);
		arr[0] = '\0';
		return (arr);
	}
	if (size > 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	arr = (unsigned char *)malloc(nmemb * size);
	if (arr == NULL)
		return (NULL);
	ft_bzero(arr, nmemb * size);
	return ((void *)arr);
}
/*
TODO: CHECK man and original.
return (NULL);
*/
