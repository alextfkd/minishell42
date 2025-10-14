/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 13:15:03 by htsutsum          #+#    #+#             */
/*   Updated: 2025/05/04 10:14:03 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (size != 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	ptr = (void *)malloc(nmemb * size);
	if (ptr != NULL)
		ft_bzero(ptr, nmemb * size);
	return (ptr);
}
// int main(void)
// {
//     size_t nmemb = SIZE_MAX;
//     size_t size = 2;

//      printf("SIZE_MAX = %zu\n",(size_t)SIZE_MAX);

//     void *ptr = ft_calloc(nmemb, size);
//     if (ptr == NULL)
//         printf("オーバーフローが検出されました（NULL）\n");
//     else {
//         printf(" オーバーフローが検出されませんでした（ptr = %p）\n", ptr);
//         free(ptr);
//     }

//     return (0);
// }