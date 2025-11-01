/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_shell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 01:59:40 by marvin            #+#    #+#             */
/*   Updated: 2025/11/01 16:06:42 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_exec_cmd_test(char *input, t_app *app, t_loglevel log_level);

int	execute_cmd(char *input, char **envp, t_loglevel log_level)
{
	t_app	app;

	(void)log_level;
	log_debug_show_input(input, LOG_QUIET);
	setup_app(&app, envp);
	_exec_cmd_test(input, &app, LOG_DEBUG);
	clear_app(&app);
	return (0);
}

static void	_exec_cmd_test(char *input, t_app *app, t_loglevel log_level)
{
	t_token		*head_token;
	t_astree	*ast_root;

	ast_root = NULL;
	log_debug_show_input("running _exec_cmd_test()", log_level);
	log_debug_show_input(input, log_level);
	head_token = tokenize(input);
	log_debug_show_token(head_token, log_level);
	if (head_token)
	{
		ast_root = parse_pipeline(&head_token);
		if (ast_root)
		{
			log_debug_show_ast(ast_root, LOG_DEBUG);
			execute_pipeline(ast_root, app);
			reset_stdio(app);
			clear_astree(ast_root);
		}
	}
	free_tokens(head_token);
}

int	interactive_shell(t_shell *shell, char **envp)
{
	t_ms_buf	*ms_buf;
	t_status	status;
	t_app		app;

	setup_app(&app, envp);
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
	clear_app(&app);
	return (status);
}
