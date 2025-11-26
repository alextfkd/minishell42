/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:16:49 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/26 11:04:38 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Print an error message for builtin command.
 *
 * @param cmd
 * @param i If i is 0,the argument is not display.
 * @param msg  The error message to display
 */
void	print_builtin_cmd_error(t_cmd *cmd, int i, const char *msg)
{
	char	*str;

	str = msg;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->argv[0], 2);
	ft_putstr_fd(": ", 2);
	if (i != 0)
	{
		ft_putstr_fd("`", 2);
		ft_putstr_fd(cmd->argv[i], 2);
		ft_putstr_fd("': ", 2);
	}
	ft_putendl_fd(str, 2);
}
