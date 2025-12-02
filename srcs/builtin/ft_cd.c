/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:54:19 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/30 06:29:38 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	_change_dir(t_cmd *cmd, char *path);
static char	*_update_env_pwds(t_app *app, t_cmd *cmd, char *old_pwd);
static char	*_get_target_path(t_app *app, t_cmd *cmd, int *print_pwd_flag);

/**
 * @brief The empty cd func,we have to program it correctly
 *
 *
 * @param app
 * @param cmd
 * @return int
 */
int	ft_cd(t_app *app, t_cmd *cmd)
{
	char	*target_path;
	char	*old_pwd;
	char	*new_pwd;
	int		print_pwd_flag;

	print_pwd_flag = 0;
	if (cmd->argc > 2)
		return (print_cmd_error(cmd, 0, "too many arguments", 0), 1);
	old_pwd = get_current_dir(app);
	if (!old_pwd)
		return (print_cmd_error(cmd, 0, strerror(errno), 0), 1);
	target_path = _get_target_path(app, cmd, &print_pwd_flag);
	if (!target_path)
		return (free(old_pwd), 1);
	if (_change_dir(cmd, target_path))
		return (free(old_pwd), 1);
	new_pwd = _update_env_pwds(app, cmd, old_pwd);
	if (!new_pwd)
		return (free(old_pwd), 1);
	if (print_pwd_flag)
		printf("%s\n", new_pwd);
	free(old_pwd);
	free(new_pwd);
	return (0);
}

/**
 * @brief Get the target path object
 *
 * @param app
 * @param cmd
 * @param print_pwd_flag
 * @return char*
 */
static char	*_get_target_path(t_app *app, t_cmd *cmd, int *print_pwd_flag)
{
	char	*path;

	if (cmd->argc == 1)
	{
		path = get_env_value(app->env_list, HOME);
		if (!path)
		{
			print_cmd_error(cmd, 0, "HOME not set", 0);
			return (NULL);
		}
	}
	else if (ft_strcmp(cmd->argv[1], "-") == 0)
	{
		path = get_env_value(app->env_list, OLDPWD);
		if (!path)
		{
			print_cmd_error(cmd, 0, "OLDPWD not set", 0);
			return (NULL);
		}
		*print_pwd_flag = 1;
	}
	else
		path = cmd->argv[1];
	return (path);
}

/**
 * @brief This is a wrapper function for chdir.
 *
 * @param path
 * @return int
 */
static int	_change_dir(t_cmd *cmd, char *path)
{
	if (chdir(path) == -1)
	{
		print_cmd_error(cmd, 1, strerror(errno), 0);
		return (1);
	}
	return (0);
}

/**
 * @brief Updates the PWD and OLDPWD envviroment variables
 *
 * This function uses the get_current_dir() function
 * to retrieve the full path of the PWD again.
 *
 * @param env_list
 * @param cmd
 * @param old_pwd
 * @return int
 */
static char	*_update_env_pwds(t_app *app, t_cmd *cmd, char *old_pwd)
{
	char	*new_pwd;

	new_pwd = get_current_dir(app);
	if (!new_pwd)
		return (print_cmd_error(cmd, 0, strerror(errno), 0), NULL);
	if (set_env_value(&app->env_list, PWD, new_pwd))
		return (free(new_pwd), NULL);
	if (set_env_value(&app->env_list, OLDPWD, old_pwd))
		return (free(new_pwd), NULL);
	if (handle_update_env(app) != 0)
		return (free(new_pwd), NULL);
	return (new_pwd);
}
