/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:16:49 by htsutsum          #+#    #+#             */
/*   Updated: 2025/12/03 18:22:23 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Reterievs the current working directory as allocated string.
 *
 * @return char* Pointer to the current working string,or NULL on error.
 */
char	*get_current_dir(t_app *app)
{
	char	*pwd_path;
	char	*env_pwd;

	pwd_path = getcwd(NULL, 0);
	if (pwd_path)
		return (pwd_path);
	env_pwd = get_env_value(app->env_list, PWD);
	if (env_pwd)
		return (ft_strdup(env_pwd));
	return (NULL);
}

/**
 * @brief Print an error message for command.
 *
 * @param cmd
 * @param i If i is 0,the argument is not display.
 * @param msg  The error message to display
 */
void	print_cmd_error(
	char *cmd_name,
	int i,
	const char *msg,
	int quate_flag)
{
	char	*str;

	str = (char *)msg;
	ft_putstr_fd("minishell: ", 2);
	if (cmd_name != NULL)
	{
		ft_putstr_fd(cmd_name, 2);
		ft_putstr_fd(": ", 2);
	}
	if (i != 0)
	{
		if (quate_flag)
			ft_putstr_fd("`", 2);
		ft_putstr_fd(cmd_name, 2);
		if (quate_flag)
			ft_putstr_fd("'", 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(str, 2);
}

void	free_shell_exit(t_app *app, int exit_status)
{
	if (app && app->shell)
		free_shell(app->shell);
	exit(exit_status);
}
