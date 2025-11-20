/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 06:27:07 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/21 02:29:28 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			return (builtin_map[i].type);
		i++;
	}
	return (BT_NOT_BULTIN);
}
