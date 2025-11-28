/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_app.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 10:58:24 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/28 00:20:13 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	_init_env_vars(t_app *app, char **envp);

/**
 * @brief Initializes the main application structure (t_app),
 * duplicates standard I/O,and copies the environment variables.
 *
 * @param app
 * @param envp
 * @return * int
 */
t_app	*setup_app(char **envp, t_shell *shell)
{
	t_app		*app;

	app = (t_app *)ft_calloc(1, sizeof(t_app));
	if (!app)
		return (NULL);
	app->shell = shell;
	app->original_stdin = dup(STDIN_FILENO);
	app->original_stdout = dup(STDOUT_FILENO);
	if (app->original_stdin == -1 || app->original_stdout == -1)
		return (perror("minishell: dup stdio"), NULL);
	if (_init_env_vars(app, envp))
		return (free_app(app), NULL);
	append_args_to_env_list(OLDPWD, &app->env_list);
	if (handle_update_env(app) != 0)
		return (NULL);
	if (!app->envp)
		return (free_app(app), NULL);
	return (app);
}

/**
 * @brief Initializes the enviroment varliables
 *
 * @param app
 * @param envp
 * @return int
 */
static int	_init_env_vars(t_app *app, char **envp)
{
	char	**tmp;

	app->envp = dup_env(envp);
	if (!app->envp)
		return (1);
	app->env_list = envp_to_env_list(app->envp);
	if (!app->env_list)
		return (1);
	tmp = app->envp;
	app->envp = NULL;
	ft_free_tab(tmp);
	return (0);
}

/**
 * @brief Cleans up and frees all resources held
 * by the main application structure.
 *
 * @param app
 * @return int
 */
void	free_app(t_app *app)
{
	if (app->envp)
		ft_free_tab(app->envp);
	if (app->env_list)
		free_env_list(app->env_list);
	if (app->cmd_list)
		free_list(&app->cmd_list);
	if (app->astree_root)
		astree_clear(&app->astree_root);
	if (app->token_head)
		free_tokens(app->token_head);
	if (app->original_stdin != -1)
		close(app->original_stdin);
	if (app->original_stdout != -1)
		close(app->original_stdout);
	free(app);
}

/**
 * @brief Resets standard input and output file descriptors
 * to their original state.
 *
 * @param app
 */
void	reset_stdio(t_app *app)
{
	if (dup2(app->original_stdin, STDIN_FILENO) < 0)
		perror("minnishell: reset stdin");
	if (dup2(app->original_stdout, STDOUT_FILENO) < 0)
		perror("misnishell: reset stdout");
}
