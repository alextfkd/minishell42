/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_shell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 01:59:40 by marvin            #+#    #+#             */
/*   Updated: 2025/11/18 09:11:11 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	_exec_cmd_test(char *input, t_app *app, t_loglevel log_level);

int	execute_cmd(char *input, t_app *app, t_loglevel log_level)
{
	(void)log_level;
	log_debug_show_input(input, LOG_QUIET);
	_exec_cmd_test(input, app, log_level);
	return (0);
}

static int	_exec_cmd_test(char *input, t_app *app, t_loglevel log_level)
{
	t_token		*head_token;
	t_astree	*ast_root;

	log_debug_show_input("running _exec_cmd_test()", log_level);
	log_debug_show_input(input, log_level);
	head_token = tokenize(input);
	if (!head_token || head_token->state != S_NORMAL)
		return (0);
	log_debug_show_token(head_token, log_level);
	if (head_token)
	{
		ast_root = create_astree_from_tokens(&head_token);
		if (ast_root)
		{
			parameter_expansion(app, ast_root);
			log_debug_show_ast(ast_root, log_level);
			execute_pipeline(ast_root, app);
			astree_clear(ast_root);
		}
		else
			free_tokens(head_token);
	}
	free_tokens(head_token);
	reset_stdio(app);
	return (0);
}

static char	*readline_with_nl(char *prompt)
{
	char	*buf;
	char	*tmp;

	tmp = readline(prompt);
	if (tmp == NULL)
	{
		return (NULL);
	}
	add_history(tmp);
	buf = ft_strjoin(tmp, "\n");
	free (tmp);
	if (buf == NULL)
	{
		return (NULL);
	}
	return (buf);
}

static int	_is_eof(t_ms_buf *t_ms_buf)
{
	if (!t_ms_buf)
		return (-1);
	if (!(t_ms_buf->rl_buf))
		return (1);
	return (0);
}

int	interactive_shell(t_shell *shell)
{
	t_ms_buf			*ms_buf;

	log_debug("MINISHELL INTERACTIVE MODE", shell->loglevel);
	set_sigaction(shell);
	ms_buf = shell->ms_buf;
	while (1)
	{
		log_debug_ms_buf(shell);
		if (ms_buf->tmp_buf == NULL)
			ms_buf->rl_buf = readline_with_nl(FT_PROMPT);
		else
			ms_buf->rl_buf = readline_with_nl(">");
		if (g_sig_received == 2)
			shell->status = 130;
		if (_is_eof(ms_buf))
		{
			free_readline_buf(ms_buf);
			break ;
		}
		exec_line(shell);
	}
	write(1, "exit\n", 5);
	rl_clear_history();
	return (shell->status);
}
