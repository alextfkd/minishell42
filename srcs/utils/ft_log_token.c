/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 23:08:11 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/01 01:41:15 by htsutsum         ###   ########.fr       */
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

	current = head;
	log_debug("--- Token List Start ---", log_level);
	if (head == NULL)
		log_debug("Token list empyt or NULL", log_level);
	i = 0;
	while (current != NULL)
	{
		if (current->data != NULL && log_level == LOG_DEBUG)
			printf("[%d] kind: %-18s | value: [%s]\n",
				i, _get_token_kind(current->tk), current->data);
		current = current->next;
		i++;
	}
	log_debug("---- Token list end ---", LOG_DEBUG);
}
