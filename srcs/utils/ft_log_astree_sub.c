/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log_astree_sub.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 05:25:43 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/07 05:35:30 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Retrieves the string representation of a redirection token type.
 *
 * @param red A pointer to the redirection structure containing the token type.
 * @return const char The string symbol of the redirection type,
 *         or "?" if unknown
 */
static const char	*_get_red_types(t_red *red)
{
	if (red->tk == TK_RED_IN)
		return ("<");
	else if (red->tk == TK_RED_HEREDOC)
		return ("<<");
	else if (red->tk == TK_RED_OUT)
		return (">");
	else if (red->tk == TK_RED_APPEND)
		return (">>");
	else
		return ("?");
}

/**
 * @briefP rints the list of redirections associated with a command.
 *
 * Iterates through the linked list of 't_red' structures and
 * prints the redirection type and the target file/delimiter
 * in the format: (Reds: [<:'file1', >>:'file2'])
 *
 * @param red The head of the 't_red' linked list
 */
void	print_redirections(t_red *red)
{
	if (red)
		printf(" (Red: [");
	while (red)
	{
		printf("%s:'%s'", _get_red_types(red), red->file);
		if (red->next)
			printf(", ");
		red = red->next;
	}
	if (red)
		printf("])");
}
