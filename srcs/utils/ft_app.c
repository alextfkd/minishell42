/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_app.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 10:58:24 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/30 18:12:34 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	_init_env_vars(t_app *app, char **envp);
static char	*_get_minishell_full_path(t_app *app, char *name);

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
	app->original_stdin = -1;
	app->original_stdout = -1;
	app->shell = shell;
	app->original_stdin = dup(STDIN_FILENO);
	app->original_stdout = dup(STDOUT_FILENO);
	if (app->original_stdin == -1 || app->original_stdout == -1)
	{
		perror("minishell: dup failed");
		return (free_app(app), NULL);
	}
	if (_init_env_vars(app, envp))
		return (free_app(app), NULL);
	if (handle_update_env(app) != 0)
		return (free_app(app), NULL);
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
	char	*name;
	char	*full_path;

	app->envp = dup_env(envp);
	if (!app->envp)
		return (1);
	app->env_list = envp_to_env_list(app->envp);
	if (!app->env_list)
		return (ft_free_tab(app->envp), 1);
	tmp = app->envp;
	app->envp = NULL;
	ft_free_tab(tmp);
	if (app->shell && app->shell->argv)
		name = app->shell->argv[0];
	else
		return (1);
	full_path = _get_minishell_full_path(app, name);
	if (!full_path)
		return (1);
	if (set_env_value(&app->env_list, "_", full_path) != 0)
		return (free(full_path), 1);
	free(full_path);
	append_args_to_env_list(OLDPWD, &app->env_list);
	return (0);
}

/**
 * @brief Get the minishell full path object
 *
 * @param app
 * @param name
 * @return char*
 */
static char	*_get_minishell_full_path(t_app *app, char *name)
{
	char	*pwd;
	char	*tmp;
	char	*full_path;

	if (name && name[0] == '/')
		return (ft_strdup(name));
	pwd = get_current_dir(app);
	if (!pwd)
	{
		print_cmd_error(NULL, 0, strerror(errno), 0);
		return (NULL);
	}
	tmp = ft_strjoin(pwd, "/");
	free(pwd);
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, name);
	free(tmp);
	return (full_path);
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
		perror("minishell: reset stdout");
}
