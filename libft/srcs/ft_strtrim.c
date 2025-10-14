/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:34:22 by htsutsum          #+#    #+#             */
/*   Updated: 2025/05/06 11:13:09 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	head;
	size_t	tail;

	if (s1 == NULL || set == NULL)
		return (ft_strdup(""));
	head = 0;
	while (s1[head] && ft_strchr(set, (int)s1[head]))
		head++;
	tail = ft_strlen(s1) - 1;
	while (tail > head && ft_strrchr(set, (int)s1[tail]))
		tail--;
	if (tail < head)
		return (ft_strdup(""));
	return (ft_substr(s1, head, tail - head + 1));
}
// int main(void)
// {
// 	char const s[] = "<<<<<ab>cdef>>>>>>";
// 	char const a[] = "<<<>>>>>";
// 	char const b[] = "";

// 	char const set[] = "<>";
// 	char *t,*at,*ab;

// 	t = ft_strtrim(s,set);
// 	printf("s %s\nset %s\ntrim %s\n",s,set,t);
// 	free(t);
// 	t = ft_strtrim(a,set);
// 	printf("s %s\nset %s\ntrim %s\n",a,set,t);
// 	free(t);
// 	t = ft_strtrim(a,set);
// 	printf("s %s\nset %s\ntrim %s\n",b,set,t);
// 	free(t);
// 	return (0);
// }