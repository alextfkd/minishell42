/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 07:30:03 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/28 20:31:13 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	_is_n_option(char *opt);
static int	_print_args(char **argv, int start);

/**
 * @brief The echo func
 * @param app
 * @param cmd
 * @return int
 */
int	ft_echo(t_app *app, t_cmd *cmd)
{
	int	i;
	int	n_flag;

	(void)app;
	if (cmd->argc == 1)
		return (ft_putstr_fd("\n", 1), 0);
	n_flag = 0;
	i = 1;
	while (cmd->argv[i] && _is_n_option(cmd->argv[i]))
	{
		n_flag = 1;
		i++;
	}
	_print_args(cmd->argv, i);
	if (!n_flag)
		ft_putstr_fd("\n", 1);
	return (0);
}

static int	_is_n_option(char *opt)
{
	int	i;

	if (!opt)
		return (0);
	i = 0;
	if (opt[i] != '-')
		return (0);
	i++;
	if (opt[i] == '\0')
		return (0);
	while (opt[i] == 'n')
		i++;
	if (opt[i] == '\0')
		return (1);
	return (0);
}

static int	_print_args(char **argv, int start)
{
	int	i;

	i = start;
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	return (0);
}
