/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:48:20 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/18 16:26:46 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// Check whether the command is a built-in command
static int	_is_builtin_cmd(t_cmd *cmd)
{
	int			i;
	const char	*b_cmd[] = {"echo", "cd", "pwd", "export", "unset", "env",
		"exit", NULL};

	if (!cmd || !cmd->av || !cmd->av[0])
		return (1);
	i = 0;
	while (b_cmd[i] != NULL)
	{
		if (ft_strcmp(cmd->av[0], b_cmd[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

// create one shot cmd
static t_cmd	*_create_cmd(char **av)
{
	int		i;
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
	{
		return (NULL);
	}
	cmd->av = av;
	i = 0;
	while (av[i] != 0)
		i++;
	cmd->ac = i;
	return (cmd);
}

// free t_cmd allocated memory
static void	_free_cmd(t_cmd *cmd)
{
	if (cmd->av)
		ft_free_tab(cmd->av);
	free(cmd);
}

// execute one shot cmd
int	exec_cmd(char *input, char **ep)
{
	t_cmd	*cmd;
	char	**av;
	int		status;

	av = ft_split(input, ' ');
	if (!av || !av[0])
	{
		if (av)
			free(av);
		return (0);
	}
	cmd = _create_cmd(av);
	if (!cmd)
	{
		free(av);
		return (1);
	}
	if (_is_builtin_cmd(cmd))
		return (printf("exec builtin cmd : %s\n", cmd->av[0]), 0);
	else
		status = exec_shell_cmd(cmd, ep);
	_free_cmd(cmd);
	return (status);
}
