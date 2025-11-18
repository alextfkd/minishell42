/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_shell copy.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 01:59:40 by marvin            #+#    #+#             */
/*   Updated: 2025/11/18 09:40:48 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	_exec_cmd_test(char *input, t_app *app, t_loglevel log_level);

int	execute_cmd(char *input, t_app *app, t_loglevel log_level)
{
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
