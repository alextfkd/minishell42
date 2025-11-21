/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 08:17:10 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/11/21 08:28:27 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Create a freeable env key candidate from the given arg value.
 * 
 * $PATH -> (PATH value in env)
 * 
 * '$PATH' -> $PATH
 * 
 * "$PATH" -> (PATH value in env)
 * 
 * @param argv Argv[i] which is contained in t_astree->cmd->argv.
 * @return char* 
 */
char	*create_env_key_candidate(char *argv, int *status)
{
	char	*key_candidate;
	size_t	len;

	*status = 0;
	if (!argv)
	{
		*status = 1;
		return (NULL);
	}
	len = ft_strlen(argv);
	if (ft_strncmp(argv, "$", 1) == 0)
		key_candidate = ft_substr(argv, 1, len - 1);
	else if (ft_strncmp(argv, "\"$", 2) == 0 && argv[len - 1] == '\"')
		key_candidate = ft_substr(argv, 2, len - 3);
	else
		return (NULL);
	if (key_candidate == NULL)
	{
		*status = 1;
		return (NULL);
	}
	return (key_candidate);
}

int	overwrite_argv(char **argv_i, char *new_argv)
{
	if (argv_i == NULL || *argv_i == NULL)
		return (1);
	free(*argv_i);
	*argv_i = ft_strdup(new_argv);
	if (*argv_i == NULL)
		return (1);
	return (0);
}

int	trim_quotes(char **argv_i)
{
	char	*tmp;

	if (argv_i == NULL || *argv_i == NULL)
		return (1);
	tmp = ft_strtrim(*argv_i, "\'\"");
	if (tmp == NULL)
		return (1);
	free(*argv_i);
	*argv_i = tmp;
	return (0);
}
