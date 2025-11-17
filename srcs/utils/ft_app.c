/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_app.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 10:58:24 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/17 12:08:34 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define OLDPWD "OLDPWD"

/**
 * @brief Initializes the main application structure (t_app),
 * duplicates standard I/O,and copies the environment variables.
 *
 * @param app
 * @param envp
 * @return * int
 */
t_app	*setup_app(char **envp, int *shell_status)
{
	t_app		*app;
	char		**old_envp;

	app = (t_app *)ft_calloc(1, sizeof(t_app));
	if (!app)
		return (NULL);
	app->exit_status = 0;
	app->shell_status = shell_status;
	app->original_stdin = dup(STDIN_FILENO);
	app->original_stdout = dup(STDOUT_FILENO);
	if (app->original_stdin == -1 || app->original_stdout == -1)
		return (perror("minishell: dup stdio"), NULL);
	app->envp = dup_env(envp);
	if (!app->envp)
		return (free_app(app), NULL);
	app->env_list = envp_to_env_list(app->envp);
	if (!app->env_list)
		return (free_app(app), NULL);
	append_args_to_env_list(OLDPWD, &app->env_list);
	old_envp = app->envp;
	app->envp = rebuild_envp(app->env_list, old_envp);
	if (!app->envp)
		return (free_app(app), NULL);
	return (app);
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
	close(app->original_stdin);
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
