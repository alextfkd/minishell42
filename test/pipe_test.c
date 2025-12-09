/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 19:11:23 by htsutsum          #+#    #+#             */
/*   Updated: 2025/12/05 21:30:40 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig_received = 0;

static void	_attach_ast_and_token_ptr(t_app *app,
				t_astree *astree_root, t_token *head);
static void	_detach_ast_and_token_ptr(t_app *app);
static int	_status_1_return(t_shell *shell, t_token *head, t_astree *root);
static void	_cleanup_all(t_shell *shell, t_token *head_token,
				t_astree **ast_head);

int	main(int argc, char **argv, char **envp)
{
	t_shell		*shell;
	t_token		*head_token;
	t_astree	*ast_root;
	t_astree	*ast_head;
	int			exit_status;

	if (argc != 2)
		return (1);
	shell = create_t_shell(argc, argv, envp);
	if (shell == NULL)
		return (1);
	shell->status = 0;
	head_token = tokenize(argv[1], &(shell->status));
	if (!head_token || head_token->state != S_NORMAL || shell->status != 0)
		return (1);
	ast_root = create_astree_from_tokens(&head_token, &(shell->status));
	ast_head = ast_root;
	if (ast_root == NULL)
		return (_status_1_return(shell, NULL, ast_root));
	if (parameter_expansion(shell->app, ast_root) != 0)
		return (_status_1_return(shell, head_token, ast_root));
	_attach_ast_and_token_ptr(shell->app, ast_root, head_token);
	exit_status = execute_pipeline(ast_root, shell->app);
	_cleanup_all(shell, head_token, &ast_head);
	return (exit_status);
}

static void	_cleanup_all(
	t_shell *shell,
	t_token *head_token,
	t_astree **ast_head)
{
	astree_clear(ast_head);
	free_tokens(head_token);
	_detach_ast_and_token_ptr(shell->app);
	reset_stdio(shell->app);
	free_shell(shell);
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
