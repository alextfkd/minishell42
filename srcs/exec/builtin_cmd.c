/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 06:27:07 by htsutsum          #+#    #+#             */
/*   Updated: 2025/12/04 05:58:41 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_reset_std_fd(int tmp_stdin, int tmp_stdout);

int	execute_builtin_parent(t_cmd *cmd, t_app *app)
{
	int	status;
	int	tmp_stdin;
	int	tmp_stdout;
	int	red_status;

	log_debug("execute_builtin_parent", app->shell->loglevel);
	tmp_stdin = dup(STDIN_FILENO);
	tmp_stdout = dup(STDOUT_FILENO);
	if (tmp_stdin == -1 || tmp_stdout == -1)
	{
		ft_putendl_fd("minishell: dup bultin parent", 2);
		return (1);
	}
	red_status = handle_redirections(cmd->red, app);
	if (red_status != 0)
	{
		_reset_std_fd(tmp_stdin, tmp_stdout);
		return (red_status);
	}
	status = execute_builtin_cmd(cmd, app);
	_reset_std_fd(tmp_stdin, tmp_stdout);
	return (status);
}

int	execute_builtin_cmd(t_cmd *cmd, t_app *app)
{
	int								status;
	const t_builtin_entry			*entry;
	static const t_builtin_entry	map[] = {
	{BT_PWD, ft_pwd},
	{BT_ENV, ft_env},
	{BT_EXPORT, ft_export},
	{BT_UNSET, ft_unset},
	{BT_CD, ft_cd},
	{BT_ECHO, ft_echo},
	{BT_EXIT, ft_exit},
	{BT_NOT_BULTIN, NULL },
	};

	status = -1;
	entry = map;
	while (entry->type != BT_NOT_BULTIN)
	{
		if (entry->type == get_builtin_type(cmd) && entry->func != NULL)
		{
			status = entry->func(app, cmd);
			break ;
		}
		entry++;
	}
	return (status);
}

/**
 * @brief Get the builtin type object
 *
 * @param cmd
 * @return t_builtin_type
 */
t_builtin_type	get_builtin_type(t_cmd *cmd)
{
	int							i;
	static const t_builtin_map	builtin_map[] = {
	{"cd", BT_CD},
	{"export", BT_EXPORT},
	{"unset", BT_UNSET},
	{"exit", BT_EXIT},
	{"echo", BT_ECHO},
	{"pwd", BT_PWD},
	{"env", BT_ENV},
	{NULL, BT_NOT_BULTIN},
	};

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (BT_NOT_BULTIN);
	i = 0;
	while (builtin_map[i].name != NULL)
	{
		if (ft_strcmp(cmd->argv[0], builtin_map[i].name) == 0)
		{
			return (builtin_map[i].type);
		}
		i++;
	}
	return (BT_NOT_BULTIN);
}

static void	_reset_std_fd(int tmp_stdin, int tmp_stdout)
{
	dup2(tmp_stdin, STDIN_FILENO);
	dup2(tmp_stdout, STDOUT_FILENO);
	close(tmp_stdin);
	close(tmp_stdout);
}
