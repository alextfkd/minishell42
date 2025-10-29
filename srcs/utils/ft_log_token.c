/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 23:08:11 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/28 01:16:27 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	*_get_token_kind(t_tokenkind tk)
{
	if (tk == TK_INIT)
		return ("TK_INIT");
	else if (tk == TK_CHAR)
		return ("TK_CHAR");
	else if (tk == TK_PIPE)
		return ("TK_PIPE");
	else if (tk == TK_SEMI)
		return ("TK_SEMI");
	else if (tk == TK_REDI_OUT_TRUC)
		return ("TK_REDI_OUT_TRUC");
	else if (tk == TK_REDI_OUT_APPEND)
		return ("TK_REDI_OUT_APPEND");
	else if (tk == TK_REDI_IN_FILE)
		return ("TK_REDI_IN_FILE");
	else if (tk == TK_REDI_IN_HEREDOC)
		return ("TK_REDI_IN_HEREDOC");
	else
		return ("UNKNOWN");
}

void	log_debug_show_token(t_token *head)
{
	t_token	*current;
	int		i;

	current = head;
	log_debug("--- Token List Start ---", LOG_DEBUG);
	if (head == NULL)
		log_debug("Token list empyt or NULL", LOG_DEBUG);
	i = 0;
	while (current != NULL)
	{
		if (current->val != NULL)
			printf("[%d] kind: %-18s | value: [%s]\n",
				i, _get_token_kind(current->tk), current->val);
		current = current->next;
		i++;
	}
	log_debug("---- Token list end ---", LOG_DEBUG);
}
