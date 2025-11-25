/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_mng.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 09:40:06 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/24 23:30:15 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	_append_env_node(t_env **env_list, char *key, char *value);

/**
 * @brief Searches the environment list for a specific key
 * and returns its value.
 *
 * @param env_list
 * @param key
 * @return char*
 */
char	*get_env_value(t_env *env_list, const char *key)
{
	if (!env_list || !key)
		return (NULL);
	while (env_list)
	{
		if (ft_strcmp(env_list->key, key) == 0 && env_list->is_set)
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}

/**
 * @brief Sets an environment variable. Updates if exists, creates if not.
 * @param env_list
 * @param key
 * @param value
 * @return int 0 on success, 1 on error
 */
int	set_env_value(t_env **env_list, char *key, char *value)
{
	t_env	*current;
	char	*new_val;

	current = *env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			new_val = ft_strdup(value);
			if (!new_val)
				return (perror("minishell: malloc"), 1);
			if (current->value)
				free(current->value);
			current->value = new_val;
			current->is_set = ENV_SET;
			return (0);
		}
		current = current->next;
	}
	return (_append_env_node(env_list, key, value));
}

/**
 * @brief Create and append a new environment node.
 *
 * This function duplicates the provided key and value strings to ensure
 * independent memory management. It handles potential malloc failures
 * by cleaning up any partially allocated memory before returning.
 *
 * @param env_list
 * @param key
 * @param value
 * @return int
 */
static int	_append_env_node(t_env **env_list, char *key, char *value)
{
	t_env	*new_node;
	char	*key_dup;
	char	*val_dup;

	key_dup = ft_strdup(key);
	val_dup = ft_strdup(value);
	if (!key_dup || !val_dup)
	{
		if (key_dup)
			free(key_dup);
		if (val_dup)
			free(val_dup);
		return (perror("minishell: malloc"), 1);
	}
	new_node = env_new_node(key_dup, val_dup, ENV_SET);
	if (!new_node)
	{
		free(key_dup);
		free(val_dup);
		return (1);
	}
	env_list_add_back(env_list, new_node);
	return (0);
}

/**
 * @brief Updates the "_" environment variable with the last argument
 *  of the command.
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
		app->envp = rebuild_envp(app->env_list, app->envp);
	if (resolved_path)
		free(resolved_path);
}
