/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_shell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 01:59:40 by marvin            #+#    #+#             */
/*   Updated: 2025/10/20 06:20:01 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	_exec_cmd_test(char *input, char **envp);

int	execute_cmd(char *input, char **envp, t_loglevel log_level)
{
	(void)log_level;
	(void)envp;
	log_debug_show_input(input, LOG_DEBUG);
	_exec_cmd_test(input, envp);
	return (0);
}

static	void	_exec_cmd_test(char *input, char **envp)
{
	t_list	*pipeline;

	log_debug_show_input("running _exec_cmd_test()", LOG_DEBUG);
	log_debug_show_input(input, LOG_DEBUG);
	pipeline = parse_input(input);
	exec_pipeline(pipeline, envp);
	ft_lstclear(&pipeline, free_cmd_content);
}

int	interactive_shell(int argc, char **argv, char **envp, t_loglevel log_level)
{
	t_ms_buf	*ms_buf;
	int			status;

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
		exec_line(ms_buf, envp, log_level, &status);
		if (status != 0)
			break ;
	}
	log_debug("5. EXIT", log_level);
	rl_clear_history();
	return (delete_ms_buf(ms_buf), status);
}
