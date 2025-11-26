/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:54:19 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/26 13:04:30 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	_change_dir(char *path);

/**
 * @brief The empty cd func,we have to program it correctly
 *
 * @param app
 * @param cmd
 * @return int
 */
int	ft_cd(t_app *app, t_cmd *cmd)
{
	char	*target_path;
	// const char	*current_path;
	// int			ret;

	(void)app;
	if (cmd->argc != 2)
		return(print_builtin_cmd_error(cmd, 0, "too many arguments"), 1);

	target_path = cmd->argv[1];
	if(_change_dir(target_path))
		return (1);
	return (0);
}

static int	_change_dir(char *path)
{
	if(chdir(path) != 0)
		return(perror("minishell: cd"), 1);
	return 0;
}

// void update_env_pwds(t_env *env_list,char *current_pwd)
// {
// 	// pwd->old_pwd

// 	// pwd -> current_pwd
// }


