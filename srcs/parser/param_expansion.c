/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 00:23:38 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/11/17 00:37:57 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	_expand_child_nodes(t_app *app, t_astree *root);
static char	*_create_env_key_candidate(char *argv);

/**
 * @brief 
 * 
 * @param app 
 * @param root 
 * @return int 
 */
int	parameter_expansion(t_app *app, t_astree *root)
{
	char	*key_unquoted;
	char	*new_argv_i;
	char	*old_argv_i;
	int		i;

	if (root == NULL)
		return (0);
	if (root->type == NODE_PIPE)
		return (_expand_child_nodes(app, root));
	i = 0;
	while (i < root->cmd->argc)
	{
		key_unquoted = _create_env_key_candidate(root->cmd->argv[i]);
		new_argv_i = get_env_value(app->env_list, key_unquoted);
		if (key_unquoted)
			free(key_unquoted);
		if (new_argv_i)
		{
			old_argv_i = root->cmd->argv[i];
			root->cmd->argv[i] = ft_strdup(new_argv_i);
			free(old_argv_i);
			if (root->cmd->argv[i] == NULL)
				return (1);
		}
		i++;
	}
	return (_expand_child_nodes(app, root));
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
static char	*_create_env_key_candidate(char *argv)
{
	char	*key_candidate;
	size_t	len;

	if (!argv)
		return (NULL);
	len = ft_strlen(argv);
	key_candidate = NULL;
	if (ft_strncmp(argv, "$", 1) == 0)
		key_candidate = ft_substr(argv, 1, len - 1);
	else if (ft_strncmp(argv, "\"$", 2) == 0 && argv[len - 1] == '\"')
		key_candidate = ft_substr(argv, 2, len - 3);
	else
		key_candidate = NULL;
	return (key_candidate);
}

static int	_expand_child_nodes(t_app *app, t_astree *root)
{
	parameter_expansion(app, root->right);
	parameter_expansion(app, root->left);
	return (0);
}
