/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_shell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 01:59:40 by marvin            #+#    #+#             */
/*   Updated: 2025/10/16 02:00:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	interactive_shell(int argc, char **argv, t_loglevel log_level)
{
	char	*input;

	log_debug("MINISHELL INTERACTIVE MODE", log_level);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	(void)argc;
	(void)argv;
	input = NULL;
	while (1)
	{
		input = readline(FT_PROMPT);
		if (input == NULL)
			return (exit_with_sigeof());
		log_debug_show_input(input, log_level);
	}
}
