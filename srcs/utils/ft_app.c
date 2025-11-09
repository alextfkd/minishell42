/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_app.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 10:58:24 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/09 18:40:43 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Cleans up and frees all resources held
 * by the main application structure.
 *
 * @param app
 * @return int
 */
int	free_app(t_app *app)
{
	if (app->envp)
		ft_free_tab(app->envp);
	close(app->original_stdin);
	close(app->original_stdout);
	return (app->exit_status);
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

/**
 * @brief Initializes the main application structure (t_app),
 * duplicates standard I/O,and copies the environment variables.
 *
 * @param app
 * @param envp
 * @return * int
 */
int	setup_app(t_app *app, char **envp)
{
	app->exit_status = 0;
	app->original_stdin = dup(STDIN_FILENO);
	app->original_stdout = dup(STDOUT_FILENO);
	if (app->original_stdin == -1 || app->original_stdout == -1)
	{
		perror("minishell: dup stdio");
		return (1);
	}
	app->envp = dup_envp(envp);
	if (!app->envp)
	{
		free_app(app);
		return (1);
	}
	return (0);
}
