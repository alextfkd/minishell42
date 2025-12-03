/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 00:23:38 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/12/03 14:32:48 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	_expand_args(t_app *app, t_astree *root);
static int	_expand_redirection(t_app *app, t_astree *root);
static int	_expand_child_nodes(t_app *app, t_astree *root);

int	parameter_expansion(t_app *app, t_astree *root)
{
	int		status;

	if (root == NULL)
		return (0);
	if (root->type == NODE_PIPE)
		return (_expand_child_nodes(app, root));
	status = 0;
	status += _expand_args(app, root);
	status += _expand_redirection(app, root);
	if (status > 0)
		return (1);
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

static int	_expand_redirection(t_app *app, t_astree *root)
{
	int		status;
	t_red	*red;
	char	*new_red_file;
	char	*key_unquoted;

	status = 0;
	red = root->cmd->red;
	while (red != NULL)
	{
		key_unquoted = create_env_key_candidate(red->file, &status);
		new_red_file = get_env_value(app->env_list, key_unquoted);
		if (new_red_file)
			status += overwrite_argv(&(red->file), new_red_file);
		status += trim_quotes(&(red->file));
		if (key_unquoted)
			free(key_unquoted);
		if (status != 0)
			return (1);
		red = red->next;
	}
	return (0);
}

static int	_expand_args(t_app *app, t_astree *root)
{
	int		i;
	char	*new_argv_i;

	i = 0;
	while (i < root->cmd->argc)
	{
		new_argv_i = expand_argv(root->cmd->argv[i], app);
		if (!new_argv_i)
			return (1);
		if (overwrite_argv(&(root->cmd->argv[i]), new_argv_i))
			return (free(new_argv_i), 1);
		if (trim_quotes(&(root->cmd->argv[i])))
			return (1);
		i++;
	}
	return (0);
}
