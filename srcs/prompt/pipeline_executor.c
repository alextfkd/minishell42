/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_executor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 01:59:40 by marvin            #+#    #+#             */
/*   Updated: 2025/11/19 02:29:19 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	_status_1_return(t_shell *shell, t_token *head, t_astree *root);

int	pipeline_executor(t_shell *shell)
{
	t_token		*head_token;
	t_astree	*ast_root;

	log_debug_show_input(shell->ms_buf->sh_buf, shell->loglevel);
	head_token = tokenize(shell->ms_buf->sh_buf, &(shell->status));
	if (!head_token || head_token->state != S_NORMAL || shell->status != 0)
		return (0);
	log_debug_show_token(head_token, shell->loglevel);
	ast_root = create_astree_from_tokens(&head_token);
	if (ast_root == NULL)
		return (_status_1_return(shell, head_token, ast_root));
	log_debug_show_ast(ast_root, shell->loglevel);
	shell->status = parameter_expansion(shell->app, ast_root);
	if (shell->status != 0)
		return (_status_1_return(shell, head_token, ast_root));
	shell->status = execute_pipeline(ast_root, shell->app);
	astree_clear(ast_root);
	free_tokens(head_token);
	reset_stdio(shell->app);
	return (0);
}

static int	_status_1_return(t_shell *shell, t_token *head, t_astree *root)
{
	if (root)
		astree_clear(root);
	if (head)
		free_tokens(head);
	if (shell)
	{
		reset_stdio(shell->app);
		shell->status = 1;
	}
	return (1);
}
