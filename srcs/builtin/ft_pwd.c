/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 11:34:42 by htsutsum          #+#    #+#             */
/*   Updated: 2025/12/03 17:43:32 by htsutsum         ###   ########.fr       */
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

	path = get_current_dir(app);
	if (!path)
		return (print_cmd_error(cmd->argv[0], 0, strerror(errno), 0), 1);
	printf("%s\n", path);
	free(path);
	return (0);
}
