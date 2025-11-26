/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:16:49 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/26 17:26:35 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Reterievs the current working directory as allocated string.
 *
 * @return char* Pointer to the current working string,or NULL on error.
 */
char	*get_current_dir(void)
{
	char	*pwd_path;

	pwd_path = getcwd(NULL, 0);
	if (!pwd_path)
		return (NULL);
	return (pwd_path);
}

/**
 * @brief Print an error message for builtin command.
 *
 * @param cmd
 * @param i If i is 0,the argument is not display.
 * @param msg  The error message to display
 */
void	print_builtin_cmd_error(
	t_cmd *cmd,
	int i,
	const char *msg,
	int quate_flag)
{
	char	*str;

	str = (char *)msg;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->argv[0], 2);
	ft_putstr_fd(": ", 2);
	if (i != 0)
	{
		if (quate_flag)
			ft_putstr_fd("`", 2);
		ft_putstr_fd(cmd->argv[i], 2);
		if (quate_flag)
			ft_putstr_fd("'", 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(str, 2);
}
