/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_mng.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 09:40:06 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/18 02:23:09 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief  Rebuilds the shell's environment variable array (char**)
 * from the internal linked list.
 *
 * This function first frees the existing environment variable array
 * (`current_envp`) to prevent memory leaks. It then generates a new,
 * dynamically allocated, null-terminated string array (char**) by converting
 * the `env_list` contents.This new array is typically used when executing
 * external programs (e.g., via `execve`).
 *
 * @param env_list
 * @param current_envp
 * @return char**
*/
char	**rebuild_envp(t_env *env_list, char **current_envp)
{
	char	**new_envp;

	if (current_envp)
		ft_free_tab(current_envp);
	new_envp = env_list_to_envp(env_list);
	if (!new_envp)
		return (perror("minishell: envp update failed"), NULL);
	return (new_envp);
}

/**
 * @brief Parses an environment line ("KEY=VALUE" or "KEY"), extracts the key
 * and value,and creates a dynamically allocated t_env node.It handles all
 * memory allocation and cleanup internally upon failure.
 *
 * * @param env_line The environment string (e.g., "PATH=/bin" or "MYVAR").
 * @return t_env* A newly allocated t_env node, or NULL if parsing or
 *  allocation fails.
 */
t_env	*get_env_from_env_line(const char *env_line)
{
	char	*key;
	char	*value;
	int		is_set;
	t_env	*new_node;

	key = get_key_env_line(env_line);
	if (!key)
		return (NULL);
	value = get_value_env_line(env_line);
	if (ft_strchr(env_line, '=') != NULL)
	{
		is_set = ENV_SET;
		if (!value)
			return (free(key), NULL);
	}
	else
		is_set = ENV_UNSET;
	new_node = env_new_node(key, value, is_set);
	if (!new_node)
	{
		free(key);
		if (value)
			return (free(value), NULL);
	}
	return (new_node);
}

/**
 * @brief Extracts and allocates memory for the environment variable name (key)
 * from an "KEY=VALUE" string, or just "KEY" if no equals sign is prese
 *
 * This function handles two main cases: "KEY=VALUE" and "KEY". It dynamically
 * allocates and returns a null-terminated string containing only the key.
 *
 * @param envp_line
 * @return char*
 */
char	*get_key_env_line(const char *envp_line)
{
	char	*key;
	char	*equal_pos;
	size_t	key_size;

	equal_pos = ft_strchr(envp_line, '=');
	if (!equal_pos)
		key_size = ft_strlen(envp_line);
	else
		key_size = equal_pos - envp_line;
	if (key_size == 0)
		return (NULL);
	key = (char *)ft_calloc(key_size + 1, sizeof(char));
	if (!key)
		return (perror("minishell: key allocation failed"), NULL);
	ft_strlcpy(key, envp_line, key_size + 1);
	return (key);
}

/**
 * @brief Extracts and allocates memory
 * for the environment variable value from an "KEY=VALUE" string.
 * if '=' is not found return NULL, if value is an empty string,set it
 * to ft_strdup("").
 *
 * @param envp_line
 * @return char*
 */
char	*get_value_env_line(const char *envp_line)
{
	char			*value;
	char			*equal_pos;
	unsigned int	start_idx;
	size_t			value_size;

	equal_pos = ft_strchr(envp_line, '=');
	if (!equal_pos)
		return (NULL);
	start_idx = equal_pos + 1 - envp_line;
	value_size = ft_strlen(equal_pos + 1);
	if (value_size == 0)
		return (ft_strdup(""));
	value = ft_substr(envp_line, start_idx, value_size);
	if (!value)
		return (perror("minishell: value allocation failed"), NULL);
	return (value);
}

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
		if (ft_strcmp(env_list->key, key) == 0)
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}
