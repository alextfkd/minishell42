/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_shell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 01:59:40 by marvin            #+#    #+#             */
/*   Updated: 2025/10/19 22:37:45 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_cmd(char *input, t_loglevel log_level)
{
	(void)log_level;
	log_debug_show_input(input, LOG_DEBUG);
	return (0);
}

int	interactive_shell(int argc, char **argv, char **envp, t_loglevel log_level)
{
	t_ms_buf			*ms_buf;
	int					status;

	log_debug("MINISHELL INTERACTIVE MODE", log_level);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	(void)argc;
	(void)argv;
	status = 0;
	ms_buf = create_ms_buf();
	if (ms_buf == NULL)
		return (1);
	while (g_sig_received == 0)
	{
		log_debug_ms_buf(ms_buf, log_level);
		ms_buf->rl_buf = readline(FT_PROMPT);
		status = exec_cmd(ms_buf->rl_buf, envp);
		exec_line(ms_buf, log_level, &status);
		if (status != 0)
			break ;
	}
	log_debug("5. EXIT", log_level);
	rl_clear_history();
	return (delete_ms_buf(ms_buf), status);
}
