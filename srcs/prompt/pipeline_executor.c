/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_executor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 01:59:40 by marvin            #+#    #+#             */
/*   Updated: 2025/11/27 14:45:04 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_attach_ast_and_token_ptr(t_app *app,
				t_astree *astree_root, t_token *head);
static void	_detach_ast_and_token_ptr(t_app *app);
static int	_status_1_return(t_shell *shell, t_token *head, t_astree *root);

int	pipeline_executor(t_shell *shell)
{
	t_token		*head_token;
	t_astree	*ast_root;
	t_astree	*ast_head;

	log_debug_show_input(shell->ms_buf->sh_buf, shell->loglevel);
	head_token = tokenize(shell->ms_buf->sh_buf, &(shell->status));
	if (!head_token || head_token->state != S_NORMAL || shell->status != 0)
		return (0);
	log_debug_show_token(head_token, shell->loglevel);
	ast_root = create_astree_from_tokens(&head_token, &(shell->status));
	ast_head = ast_root;
	if (ast_root == NULL)
		return (_status_1_return(shell, head_token, ast_root));
	log_debug_show_ast(ast_root, shell->loglevel);
	shell->status = parameter_expansion(shell->app, ast_root);
	if (shell->status != 0)
		return (_status_1_return(shell, head_token, ast_root));
	_attach_ast_and_token_ptr(shell->app, ast_root, head_token);
	shell->status = execute_pipeline(ast_root, shell->app);
	shell->prev_status = shell->status;
	astree_clear(&ast_head);
	free_tokens(head_token);
	_detach_ast_and_token_ptr(shell->app);
	reset_stdio(shell->app);
	return (0);
}

static void	_attach_ast_and_token_ptr(
				t_app *app, t_astree *astree_root, t_token *head)
{
	app->astree_root = astree_root;
	app->token_head = head;
}

static void	_detach_ast_and_token_ptr(t_app *app)
{
	app->astree_root = NULL;
	app->token_head = NULL;
}

static int	_status_1_return(t_shell *shell, t_token *head, t_astree *root)
{
	if (root)
		astree_clear(&root);
	if (head)
		free_tokens(head);
	if (shell)
	{
		reset_stdio(shell->app);
		shell->status = 1;
	}
	return (1);
}
