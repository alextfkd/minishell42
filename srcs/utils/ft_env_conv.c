/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_conv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 09:09:56 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/28 00:12:42 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*_format_to_envp(char *key, char *value);

/**
 * @brief Initializes the minishell's environment by duplicating the main
 * environment variables
 *
 * This function duplicates the system's `main_envp` (environ) into a new,
 * dynamically allocated array for the shell's use, Memory is managed internally,
 * and failure at any allocation step results in cleanup and returns NULL.
 *
 * @param envp  the main enviroment variables
 * @return char**
 */
char	**dup_env(char **main_envp)
{
	int		len;
	int		i;
	char	**new;

	len = 0;
	while (main_envp[len] != NULL)
		len++;
	new = (char **)ft_calloc(len + 1, sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new[i] = ft_strdup(main_envp[i]);
		if (!new[i])
		{
			ft_free_tab(new);
			return (NULL);
		}
		i++;
	}
	new[i] = NULL;
	return (new);
}

/**
 * @brief Converts the standard external environment array (char** envp) into
 * the internal environment linked list (t_env*).
 *
 * This function iterates through the null-terminated 'envp' array, using
 * get_env_from_env_line to parse each "KEY=VALUE" string and create a
 * corresponding t_env node. Nodes are then added to the end of the list.
 *
 * @param envp
 * @return t_env*
 */
t_env	*envp_to_env_list(char **envp)
{
	t_env	*new_node;
	t_env	*env_list;
	size_t	i;

	if (!envp)
		return (NULL);
	i = 0;
	env_list = NULL;
	while (envp[i])
	{
		new_node = get_env_from_env_line(envp[i]);
		if (!new_node)
		{
			free_env_list(env_list);
			return (perror("minishell:create env_node failed"), NULL);
		}
		new_node->is_set = ENV_SET;
		env_list_add_back(&env_list, new_node);
		i++;
	}
	return (env_list);
}

/**
 * @brief Creates a dynamically allocated environment array (char**)
 * by converting the internal linked list, filtering for 'set' variables.
 *
 * This function converts the linked list (`env_list`) into a null-terminated
 * array of strings (`char**`), including only those variables where
 * `is_set == ENV_SET`. This array is suitable for passing to functions
 * like `execve`. Memory is allocated for the array and each environment string.
 *
 * @param env_list
 * @return char**
*/
char	**env_list_to_envp(t_env *env_list)
{
	char	**envp;
	size_t	envp_size;
	size_t	i;

	envp_size = env_list_size(env_list, ENV_SET);
	envp = (char **)ft_calloc(envp_size + 1, sizeof(char *));
	if (!envp)
		return (perror("minishel:envp allocation failed"), NULL);
	i = 0;
	while (env_list)
	{
		if (env_list->is_set == ENV_SET)
		{
			envp[i] = _format_to_envp(env_list->key, env_list->value);
			if (!envp[i])
			{
				perror("minishell:envp allocation failed");
				return (free_envp(envp, i), NULL);
			}
			i++;
		}
		env_list = env_list->next;
	}
	envp[i] = NULL;
	return (envp);
}

/**
 * @brief Combines a key and a value to create an environment variable string
 * in "KEY=VALUE\0" format.
 *
 * @param key
 * @param value
 * @return char
 *
**/
static char	*_format_to_envp(char *key, char *value)
{
	char	*line;
	size_t	len;
	size_t	key_len;
	size_t	value_len;

	key_len = ft_strlen(key);
	value_len = ft_strlen(value);
	len = key_len + value_len + 2;
	line = (char *)ft_calloc(sizeof(char), len);
	if (!line)
	{
		perror("minishell: format envp failed");
		return (NULL);
	}
	ft_memcpy(line, key, key_len);
	line[key_len] = '=';
	ft_memcpy(line + key_len + 1, value, value_len);
	return (line);
}
