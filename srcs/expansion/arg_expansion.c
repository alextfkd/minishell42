/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 00:23:38 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/11/21 08:25:18 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	_expand_child_nodes(t_app *app, t_astree *root);

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
		key_unquoted = create_env_key_candidate(root->cmd->argv[i], &status);
		new_argv_i = get_env_value(app->env_list, key_unquoted);
		if (new_argv_i)
			status += overwrite_argv(&(root->cmd->argv[i]), new_argv_i);
		status += trim_quotes(&(root->cmd->argv[i]));
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
