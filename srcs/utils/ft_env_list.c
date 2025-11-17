/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 09:40:06 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/15 04:51:35 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Frees all memory allocated for the environment linked list.
 *
 * @param env_list
 */
void	free_env_list(t_env *env_list)
{
	t_env	*tmp;

	while (env_list)
	{
		if (env_list->key)
			free(env_list->key);
		if (env_list->value)
			free(env_list->value);
		tmp = env_list->next;
		free(env_list);
		env_list = tmp;
	}
}

/**
 * @brief Creates and allocates memory for a new t_env node,
 *  setting its properties.
 *
 * This function takes ownership of the 'key' and 'value' pointers.
 * The caller must ensure they were dynamically allocated.
 *
 * @param envp_line
 * @return t_env*
 */

t_env	*env_new_node(char *key, char *value, int is_set)
{
	t_env	*new_node;

	new_node = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!new_node)
		return (perror("minishell: create new env_node failed"), NULL);
	new_node->key = key;
	new_node->value = value;
	new_node->is_set = is_set;
	new_node->next = NULL;
	return (new_node);
}

/**
 * @brief A flag to determine the counting behavior:
 * 0 (or any other value): Count ALL nodes.
 *
 * ENV_SET: Count ONLY nodes where is_set == ENV_SET.
 *
 * @param env_list
 * @return size_t
 */
size_t	env_list_size(t_env *env_list, int mode)
{
	size_t	size;

	size = 0;
	if (!env_list)
		return (size);
	while (env_list)
	{
		if (mode == ENV_ALL || env_list->is_set == mode)
			size++;
		env_list = env_list->next;
	}
	return (size);
}

/**
 * @brief Adds a new t_env node to the end of the environment linked list.
 *
 * @param env_list
 * @param new_node
 */
void	env_list_add_back(t_env **env_list, t_env *new_node)
{
	t_env	*last;

	if (!env_list || !new_node)
		return ;
	if (*env_list == NULL)
	{
		*env_list = new_node;
		return ;
	}
	last = env_last_list(*env_list);
	last->next = new_node;
}

/**
 * @brief Finds the last node of the environment linked list.
 *
 * @param env_list
 * @return t_env*
 */
t_env	*env_last_list(t_env *env_list)
{
	if (!env_list)
		return (NULL);
	while (env_list->next)
		env_list = env_list->next;
	return (env_list);
}
