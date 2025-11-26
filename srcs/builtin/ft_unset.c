/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 07:30:30 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/26 21:18:41 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	_remove_env_node(t_env **head_env_list, const char *key);

/**
 * @brief The built-in unset command to remove environment variables.
 *
 * This function iterates through arguments, validates the keys, and
 * removes the corresponding node from the application's environment list.
 * If any variable is successfully removed, the execve-ready envp array
 * is rebuilt.
 *
 * @param app
 * @param cmd
 * @return int
 */
int	ft_unset(t_app *app, t_cmd *cmd)
{
	int		i;
	int		update;
	int		ret;

	i = 1;
	ret = 0;
	update = 0;
	while (i < cmd->argc)
	{
		if (!is_validate_args(cmd->argv[i])
			|| ft_strchr(cmd->argv[i], '=') != NULL)
		{
			print_builtin_error(cmd, i, "not a valid identifier", 1);
			ret = 1;
		}
		else
		{
			if (_remove_env_node(&app->env_list, cmd->argv[i]))
				update++;
		}
		i++;
	}
	if (update > 0 && handle_update_env(app) != 0)
		return (1);
	return (ret);
}

/**
 * @brief Removes a single environment node with the specified key
 *  from the list.
 *
 * This static helper function searches the linked list pointed
 * to by *head_env_list for a matching key. If found, it unlinks
 * the node and frees its memory using free_env_node.
 *
 * @param head_env_list
 * @param key
 * @return int
 */
static int	_remove_env_node(t_env **head_env_list, const char *key)
{
	t_env	*current;
	t_env	*prev;

	current = *head_env_list;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev == NULL)
				*head_env_list = current->next;
			else
				prev->next = current->next;
			free_env_node(current);
			return (1);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}
