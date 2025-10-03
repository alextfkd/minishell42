/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 10:15:35 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/05/08 22:33:45 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*free_and_clear(t_list **lst, void *content, void (*del)(void *))
{
	free(content);
	ft_lstclear(lst, del);
	return (NULL);
}

static void	force_crash_undefined(void)
{
	int	*ptr;

	ptr = NULL;
	*ptr = 42;
	return ;
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_head;
	t_list	*new_node;
	void	*new_content;

	if (lst == NULL)
		return (NULL);
	if (f == NULL || del == NULL)
		force_crash_undefined();
	new_content = f(lst->content);
	new_head = ft_lstnew(new_content);
	if (new_head == NULL)
		return (free_and_clear(&new_head, new_content, del));
	lst = lst->next;
	while (lst != NULL)
	{
		new_content = f(lst->content);
		new_node = ft_lstnew(new_content);
		if (new_node != NULL)
			ft_lstadd_back(&new_head, new_node);
		else
			return (free_and_clear(&new_head, new_content, del));
		lst = lst->next;
	}
	return (new_head);
}
