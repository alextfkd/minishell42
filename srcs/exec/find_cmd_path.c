/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 22:49:41 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/21 14:48:48 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*_append_cmd_to_path(char *path, char *cmd);
static char	*_check_cmd_path(char *av0);
static char	**_get_path_dir(void);
static char	*_search_paths(char **paths, char *av0);

/**
 * @brief search for the full path of the executable file form command name
 *
 * @param av0 command name to execute (e.g.,"ls")
 * @return char* the full path to executable file. Return Null if not found.
 */
char	*find_cmd_path(char *av0)
{
	char	**paths;
	char	*cmd_path;

	cmd_path = _check_cmd_path(av0);
	if (cmd_path != NULL)
		return (cmd_path);
	paths = _get_path_dir();
	if (!paths)
		return (NULL);
	cmd_path = _search_paths(paths, av0);
	if (!cmd_path)
	{
		ft_free_tab(paths);
		return (NULL);
	}
	ft_free_tab(paths);
	return (cmd_path);
}

static char	*_append_cmd_to_path(char *path, char *cmd)
{
	char	*part_path;
	char	*cmd_path;

	part_path = ft_strjoin(path, "/");
	if (!part_path)
		return (NULL);
	cmd_path = ft_strjoin(part_path, cmd);
	free(part_path);
	if (!cmd_path)
		return (NULL);
	return (cmd_path);
}

static char	*_check_cmd_path(char *av0)
{
	if (ft_strchr(av0, '/'))
	{
		if (access(av0, F_OK) == 0)
			return (ft_strdup(av0));
		return (NULL);
	}
	return (NULL);
}

static char	**_get_path_dir(void)
{
	char	*env_path;
	char	**paths;

	env_path = getenv("PATH");
	if (!env_path)
		return (NULL);
	paths = ft_split(env_path, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

static char	*_search_paths(char **paths, char *av0)
{
	int		i;
	char	*cmd_path;

	i = 0;
	while (paths[i])
	{
		cmd_path = _append_cmd_to_path(paths[i], av0);
		if (!cmd_path)
			break ;
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}
