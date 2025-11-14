/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_mng.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 09:40:06 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/14 17:30:49 by htsutsum         ###   ########.fr       */
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
 * @brief Extracts and allocates memory
 * for the environment variable name (key) from an "KEY=VALUE" string.
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
		return (NULL);
	key_size = equal_pos - envp_line;
	key = (char *)ft_calloc(key_size + 1, sizeof(char));
	if (!key)
		return (perror("minishell: key allocation failed"), NULL);
	ft_strlcpy(key, envp_line, key_size);
	return (key);
}

/**
 * @brief Extracts and allocates memory
 * for the environment variable value from an "KEY=VALUE" string.
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
