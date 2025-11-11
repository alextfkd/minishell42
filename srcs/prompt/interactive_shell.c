/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_shell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 01:59:40 by marvin            #+#    #+#             */
/*   Updated: 2025/11/11 07:04:24 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	_exec_cmd_test(char *input, t_app *app, t_loglevel log_level);

int	execute_cmd(char *input, char **envp, t_loglevel log_level)
{
	t_app	app;

	(void)log_level;
	log_debug_show_input(input, LOG_QUIET);
	setup_app(&app, envp);
	_exec_cmd_test(input, &app, log_level);
	clear_app(&app);
	return (0);
}

static int	_exec_cmd_test(char *input, t_app *app, t_loglevel log_level)
{
	t_token		*head_token;
	t_astree	*ast_root;

	ast_root = NULL;
	log_debug_show_input("running _exec_cmd_test()", log_level);
	log_debug_show_input(input, log_level);
	head_token = tokenize(input);
	if (head_token->state != S_NORMAL)
		return (0);
	log_debug_show_token(head_token, log_level);
	if (head_token)
	{
		ast_root = parse_pipeline(&head_token);
		if (ast_root)
		{
			log_debug_show_ast(ast_root, log_level);
			execute_pipeline(ast_root, app);
			reset_stdio(app);
			astree_clear(ast_root);
		}
	}
	free_tokens(head_token);
	return (0);
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
