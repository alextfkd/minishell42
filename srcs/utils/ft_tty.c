/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tty.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 01:35:28 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/29 02:53:50 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Set the heredoc prompt object
 *
 * @return int
 */
char	*set_heredoc_prompt(void)
{
	char	*prompt;

	if (isatty(STDIN_FILENO))
		prompt = HERE_DOC_PROMPT;
	else
		prompt = NULL;
	return (prompt);
}

/**
 * @brief Set the minishell prompt object
 *
 * @param prompt1
 * @param prompt2
 */
void	set_minishell_prompt(char **prompt1, char **prompt2)
{
	if (!isatty(STDIN_FILENO))
	{
		*prompt1 = NULL;
		*prompt2 = NULL;
	}
}
