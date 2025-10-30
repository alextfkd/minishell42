/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_shell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 01:59:40 by marvin            #+#    #+#             */
/*   Updated: 2025/10/29 22:56:59 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	_exec_cmd_test(char *input, char **envp);

int	execute_cmd(char *input, char **envp, t_loglevel log_level)
{
	(void)log_level;
	(void)envp;
	log_debug_show_input(input, LOG_QUIET);
	_exec_cmd_test(input, envp);
	return (0);
}

static	void	_exec_cmd_test(char *input, char **envp)
{
	t_list	*pipeline;
	t_token	*head_token;

	log_debug_show_input("running _exec_cmd_test()", LOG_DEBUG);
	log_debug_show_input(input, LOG_DEBUG);
	head_token = tokenize(input);
	log_debug_show_token(head_token,LOG_DEBUG);
	free_tokens(head_token);
	pipeline = parse_input(input);
	exec_pipeline(pipeline, envp);
	ft_lstclear(&pipeline, free_cmd_content);
}

int	interactive_shell(t_shell *shell, char **envp)
{
	t_ms_buf	*ms_buf;
	t_status	status;

	log_debug("MINISHELL INTERACTIVE MODE", shell->loglevel);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	ms_buf = shell->ms_buf;
	status = shell->status;
	while (g_sig_received == 0)
	{
		log_debug_ms_buf(shell);
		ms_buf->rl_buf = readline(FT_PROMPT);
		exec_line(shell, envp);
		if (status != 0)
			break ;
	}
	log_debug("5. EXIT", shell->loglevel);
	rl_clear_history();
	return (status);
}
