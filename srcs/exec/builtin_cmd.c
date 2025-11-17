/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 06:27:07 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/17 22:00:27 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin_cmd(t_cmd *cmd, t_app *app)
{
	int						status;
	t_builtin_type			type;
	const t_builtin_entry	*entry;

	static const t_builtin_entry map[] = {
		{ BT_PWD,    ft_pwd },
		{ BT_ENV,    ft_env },
		{ BT_EXPORT, ft_export },
		{ BT_UNSET,  ft_unset },
		{ BT_NOT_BULTIN, NULL },
	};
	status = -1;
	type = get_builtin_type(cmd);
	entry = map;
	while (entry->type != BT_NOT_BULTIN) {
        if (entry->type == type && entry->func != NULL)
		{
            status = entry->func(app, cmd);
			break;
		}
        entry++;
    }
	if(status == -1)
		printf("execute a builtin cmd -> %s\n", cmd->argv[0]);
	return (status);
}
