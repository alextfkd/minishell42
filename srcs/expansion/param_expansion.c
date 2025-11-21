/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 00:23:38 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/11/21 07:46:41 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	_expand_child_nodes(t_app *app, t_astree *root);
static char	*_create_env_key_candidate(char *argv, int *status);
static int	_overwrite_argv(char **argv_i, char *new_argv);
static int	_trim_quotes(char **argv_i);

int	parameter_expansion(t_app *app, t_astree *root)
{
	char	*key_unquoted;
	char	*new_argv_i;
	int		status;
	int		i;

	if (root == NULL)
		return (0);
	if (root->type == NODE_PIPE)
		return (_expand_child_nodes(app, root));
	i = 0;
	while (i < root->cmd->argc)
	{
		key_unquoted = _create_env_key_candidate(root->cmd->argv[i], &status);
		new_argv_i = get_env_value(app->env_list, key_unquoted);
		if (new_argv_i)
			status += _overwrite_argv(&(root->cmd->argv[i]), new_argv_i);
		status += _trim_quotes(&(root->cmd->argv[i]));
		if (key_unquoted)
			free(key_unquoted);
		if (status != 0)
			return (1);
		i++;
	}
	return (_expand_child_nodes(app, root));
}

/**
 * @brief 
 * 
 * @param app 
 * @param root 
 * @return int 
 */
static int	_expand_child_nodes(t_app *app, t_astree *root)
{
	int	right;
	int	left;

	right = parameter_expansion(app, root->right);
	left = parameter_expansion(app, root->left);
	return (right + left);
}

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
static char	*_create_env_key_candidate(char *argv, int *status)
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

static int	_overwrite_argv(char **argv_i, char *new_argv)
{
	if (argv_i == NULL || *argv_i == NULL)
		return (1);
	free(*argv_i);
	*argv_i = ft_strdup(new_argv);
	if (*argv_i == NULL)
		return (1);
	return (0);
}

static int	_trim_quotes(char **argv_i)
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
