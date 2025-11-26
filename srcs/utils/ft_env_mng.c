/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_mng.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 09:40:06 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/26 16:59:53 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_overwrite_and_free_node(t_env *current, t_env *new_node);

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
int	set_env_value(t_env **env_list, const char *key, const char *value)
{
	t_env	*new_node;
	char	*key_dup;
	char	*val_dup;

	key_dup = ft_strdup(key);
	val_dup = ft_strdup(value);
	if (!key_dup || !val_dup)
	{
		free(key_dup);
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
	return (add_or_update_env_node(env_list, new_node));
}

/**
 * @brief Consumes a new node to update an existing one or append to the list.
 *  Searches for a node with the same key.
 *  If found: Overwrites the value using the new node's data,
 *  then frees the new node.
 *  If not found: Appends the new node to the end of the list.
 *
 * @param env_list
 * @param new_node
 * @return int
 */
int	add_or_update_env_node(t_env **env_list, t_env *new_node)
{
	t_env	*current;

	current = *env_list;
	while (current)
	{
		if (ft_strcmp(new_node->key, current->key) == 0)
		{
			_overwrite_and_free_node(current, new_node);
			return (0);
		}
		current = current->next;
	}
	env_list_add_back(env_list, new_node);
	return (0);
}

/**
 * @brief Overwrites the existing environment node's value and is_set flag
 * with the new node's information, then safely frees the new node's remnants.
 *
 *  This function handles memory ownership transfer for 'value' to prevent
 * double freeing or memory leaks.
 *
 * @param current
 * @param new_node
 */
static void	_overwrite_and_free_node(t_env *current, t_env *new_node)
{
	if (new_node->is_set == ENV_SET)
	{
		if (current->value)
			free(current->value);
		current->value = new_node->value;
		new_node->value = NULL;
		current->is_set = ENV_SET;
	}
	free_env_node(new_node);
}

/**
 * @brief Frees the memory allocated for a single environment variable node
 * (t_env).
 * * This function handles the safe deallocation of the dynamically allocated
 * strings for the key and the value, followed by the deallocation of the node
 * structure itself.
 *
 * @param node
 */
void	free_env_node(t_env *node)
{
	if (node->key)
		free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}
