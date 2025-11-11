/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 23:08:11 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/11 02:56:51 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	*_get_token_kind(t_tkind tk)
{
	if (tk == TK_CHAR)
		return ("TK_CHAR");
	else if (tk == TK_PIPE)
		return ("TK_PIPE");
	else if (tk == TK_RED_OUT)
		return ("TK_RED_OUT");
	else if (tk == TK_RED_APPEND)
		return ("TK_RED_APPEND");
	else if (tk == TK_RED_IN)
		return ("TK_RED_IN");
	else if (tk == TK_RED_HEREDOC)
		return ("TK_RED_HEREDOC");
	else
		return ("UNKNOWN");
}

void	log_debug_show_token(t_token *head, t_loglevel log_level)
{
	t_token	*current;
	int		i;

	log_debug("--- Token List Start ---", log_level);
	if (head == NULL)
	{
		log_debug("The token list is NULL.", log_level);
		return ;
	}
	if (head->data == NULL)
	{
		log_debug("The token_head->data == NULL", log_level);
		return ;
	}
	current = head;
	i = 0;
	while (current != NULL)
	{
		if (current->data != NULL && log_level <= LOG_DEBUG)
			printf("[%d] kind: %-18s | value: [%s]\n",
				i, _get_token_kind(current->tk), current->data);
		current = current->next;
		i++;
	}
	log_debug("---- Token list end ---", log_level);
}
