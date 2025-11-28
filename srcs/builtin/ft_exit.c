/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 07:29:47 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/28 10:08:43 by tkatsuma         ###   ########.fr       */
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
		exit_process(0, app);
	else if (cmd->argc == 2)
	{
		if (!_is_overflow(cmd->argv[1]) && _is_alphasign(cmd->argv[1]))
		{
			status = ft_atoi(cmd->argv[1]);
			if (status < 0)
				status = 256 - ((status * -1) / 256);
			else
				status = status / 256;
			exit_process(status, app);
		}
		ft_putendl_fd("minishell: exit: numeric argument required", 2);
		exit_process(0, app);
	}
	return (ft_putendl_fd("minishell: exit: too many arguments", 2), 1);
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

	if (str == NULL)
		return (0);
	p = str;
	if (ft_isdigit(*p) == 1 || *p == '-' || *p == '+')
		p++;
	while (*p != '\0')
	{
		if (ft_isdigit(*p) == 0)
			return (0);
		p++;
	}
	return (1);
}

static int	_is_overflow(const char *nptr)
{
	long	res;
	long	sign;

	res = 0;
	sign = 1;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	while (ft_isdigit(*nptr) != 0)
	{
		if (sign == 1 && res > INT_MAX / 10)
			return (1);
		if (sign == 1 && 10 * res > INT_MAX - (*nptr - '0'))
			return (1);
		res = 10 * res + (*nptr++ - '0');
	}
	if (sign == -1 || res > INT_MAX)
		return (1);
	return (0);
}
