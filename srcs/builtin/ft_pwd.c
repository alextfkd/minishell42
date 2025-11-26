/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 11:34:42 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/26 16:56:41 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints the current working directory to standard output.
 *  as the buitin command "PWD"
 *
 * @return int 0 if successful,1 on error.
 */
int	ft_pwd(t_app *app, t_cmd *cmd)
{
	char	*path;

	(void)app;
	(void)cmd;
	path = get_current_dir();
	if (!path)
		return (print_builtin_cmd_error(cmd, 0, strerror(errno), 0), 1);
	printf("%s\n", path);
	free(path);
	return (0);
}
