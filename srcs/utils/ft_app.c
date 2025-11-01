/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_app.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 10:58:24 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/31 22:10:40 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// clear values of app and close stdio
int	clear_app(t_app *app)
{
	if (app->envp)
		ft_free_tab(app->envp);
	close(app->original_stdin);
	close(app->original_stdout);
	return (app->exit_status);
}

// reset stdio in main.
void	reset_stdio(t_app *app)
{
	if (dup2(app->original_stdin, STDIN_FILENO) < 0)
		perror("minnishell: reset stdin");
	if (dup2(app->original_stdout, STDOUT_FILENO) < 0)
		perror("misnishell: reset stdout");
}

// duplicate envp;
static char	**_dup_envp(char **envp)
{
	int		len;
	int		i;
	char	**new;

	len = 0;
	while (envp[len] != NULL)
		len++;
	new = (char **)ft_calloc(len + 1, sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new[i] = ft_strdup(envp[i]);
		if (!new[i])
		{
			new[i] = NULL;
			ft_free_tab(new);
			return (NULL);
		}
		i++;
	}
	new[i] = NULL;
	return (new);
}

// set up t_app
int	setup_app(t_app *app, char **envp)
{
	app->exit_status = 0;
	app->original_stdin = dup(STDIN_FILENO);
	app->original_stdout = dup(STDOUT_FILENO);
	if (app->original_stdin == -1 || app->original_stdout == -1)
	{
		perror("minishell: dup stdio");
		return (1);
	}
	app->envp = _dup_envp(envp);
	if (!app->envp)
	{
		clear_app(app);
		return (1);
	}
	return (0);
}
