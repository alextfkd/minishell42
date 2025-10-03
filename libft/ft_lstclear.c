/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 10:15:13 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/05/08 14:36:24 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;
	t_list	*prev;

	node = *lst;
	prev = *lst;
	while (node != NULL)
	{
		del(node->content);
		node = node->next;
		free(prev);
		prev = node;
	}
	*lst = NULL;
	return ;
}
