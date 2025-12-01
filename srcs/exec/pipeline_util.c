/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 00:24:35 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/28 01:01:49 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief free pipeline variables
 *
 * @param e
 * @param app
 */
void	free_pipeline_vars(t_exec *e, t_app *app)
{
	if (e->pids)
		free(e->pids);
	if (e->cmd_list)
		free_list(&e->cmd_list);
	if (app)
		app->cmd_list = NULL;
}

/**
 * @brief Cleans up a pipeline execution by terminating and waiting
 *  for child processes,// then freeing allocated memory.
 *
 * @param cmd_list
 * @param pids
 * @param count
 */
void	cleanup_pipeline(t_list *cmd_list, pid_t *pids, int count)
{
	int	i;

	(void)cmd_list;
	i = 0;
	while (i < count)
	{
		kill(pids[i], SIGTERM);
		waitpid(pids[i], NULL, 0);
		i++;
	}
}

/**
 * @brief Updates the "_" environment variable with the last argument
 *  of the command.e
 *
 * @param app
 * @param cmd
 */
void	update_underscore(t_app *app, t_cmd *cmd)
{
	char	*val_to_set;
	char	*resolved_path;

	resolved_path = NULL;
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return ;
	if (cmd->argc > 1)
		val_to_set = cmd->argv[cmd->argc - 1];
	else
	{
		if (get_builtin_type(cmd) != BT_NOT_BULTIN)
			val_to_set = cmd->argv[0];
		else
		{
			resolved_path = find_cmd_path(cmd->argv[0], app->env_list);
			if (resolved_path)
				val_to_set = resolved_path;
			else
				val_to_set = cmd->argv[0];
		}
	}
	if (set_env_value(&app->env_list, "_", val_to_set) == 0)
		handle_update_env(app);
	if (resolved_path)
		free(resolved_path);
}

/**
 * @brief Convert from astree to command list and initialize t_exec variables.
 *
 * @param e
 * @param node
 * @param app
 * @return int
 */
int	init_exec_vars(t_exec *e, t_astree *node, t_app *app)
{
	ft_bzero(e, sizeof(t_exec));
	e->cmd_list = astree2list(node);
	app->cmd_list = e->cmd_list;
	if (!e->cmd_list)
		return (1);
	e->cmd_count = ft_lstsize(e->cmd_list);
	return (0);
}

void	close_unused_fds(void)
{
	int	fd;

	fd = 3;
	while (fd < MAX_FD)
	{
		close(fd);
		fd++;
	}
}
