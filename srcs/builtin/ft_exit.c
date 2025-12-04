/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 07:29:47 by htsutsum          #+#    #+#             */
/*   Updated: 2025/12/04 04:37:58 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	_is_overflow(const char *nptr);
static int	_is_alphasign(const char *str);

/**
 * @brief exit test func,we have to program it correctly.
 *
 * @param app
 * @param cmd
 * @return int
 */
int	ft_exit(t_app *app, t_cmd *cmd)
{
	int	status;

	if (cmd->argc == 1)
		exit_process(app->shell->prev_status, app);
	if (_is_overflow(cmd->argv[1]) || !_is_alphasign(cmd->argv[1]))
	{
		ft_putendl_fd("minishell: exit: numeric argument required", 2);
		exit_process(2, app);
	}
	if (cmd->argc > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	status = ft_atoi(cmd->argv[1]);
	exit_process((status & 0xFF), app);
	return (status);
}

void	exit_process(int status, t_app *app)
{
	reset_stdio(app);
	free_tokens(app->token_head);
	app->token_head = NULL;
	free_list(&(app->cmd_list));
	app->cmd_list = NULL;
	free_ms_buf(&app->shell->ms_buf);
	app->shell->ms_buf = NULL;
	free_shell(app->shell);
	exit(status);
}

static int	_is_alphasign(const char *str)
{
	const char	*p;

	p = str;
	if (p == NULL || *p == '\0')
		return (0);
	if (*p == '-' || *p == '+')
		p++;
	if (*p == '\0')
		return (0);
	while (*p != '\0')
	{
		if (!ft_isdigit(*p))
			return (0);
		p++;
	}
	return (1);
}

static int	_is_overflow(const char *nptr)
{
	unsigned long long	res;
	long				sign;

	res = 0;
	sign = 1;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (ft_isdigit(*nptr) != 0)
	{
		if (res > (unsigned long long)LLONG_MAX / 10)
			return (1);
		if (res == (unsigned long long)LLONG_MAX / 10)
		{
			if (sign == 1 && *nptr > '7')
				return (1);
			if (sign == -1 && *nptr > '8')
				return (1);
		}
		res = 10 * res + (*nptr++ - '0');
	}
	return (0);
}
