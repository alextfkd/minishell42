/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 09:40:06 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/09 14:44:00 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
 * @brief Duplicate the main enviroment variables for the minishell.
 *
 * @param envp  the main enviroment variables
 * @return char**
 */
char	**dup_envp(char **main_envp)
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
 * @brief Searches the environment list for a specific key
 * and returns its value.
 *
 * @param env_list
 * @param key
 * @return char*
 */
char	*env_get_value(t_env *env_list, const char *key)
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
