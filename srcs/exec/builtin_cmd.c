/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 06:27:07 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/07 06:53:12 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin_cmd(t_cmd *cmd, t_app *app)
{
	int				status;
	t_builtin_type	type;
	type = get_builtin_type(cmd);

	if (type == BT_PWD)
		status = ft_pwd();
	else if (type == BT_ENV)
		status = ft_env(app);
	else
		printf("execute a builtin cmd -> %s\n", cmd->argv[0]);
	return (status);
}
