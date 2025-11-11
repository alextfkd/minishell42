/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 06:30:16 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/06 08:27:51 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	_count_argc(t_token *start, t_token *end);
static int	_is_valid_redirection_token(t_token *token);
static char	**_aquire_argv(t_token *start, int argc);
static void	_free_argv(char **argv);

/* Set array of *char to t_cmd->argv. 
The *start token is included in argv.
The redirection operator token and 
the following redirection target are excluded.
The length of array is n + 1, terminating with NULL.
*/
int	set_cmd_argv(t_cmd *cmd, t_token *start, t_token *end)
{
	int	argc;

	if (!cmd)
		log_debug("cmd is null in set_cmd_argv!", LOG_DEBUG);
	argc = _count_argc(start, end);
	if (argc < 0)
	{
		return (ft_putendl_fd(ERR_SYNTAX_TOKEN, 2), 1);
	}
	cmd->argv = _aquire_argv(start, argc);
	if (!cmd->argv)
	{
		perror("minishell: t_cmd->argv memory allocated error");
		return (1);
	}
	cmd->argc = argc;
	return (0);
}

/* Count the number of following TK_CHAR tokens as argc.
The *start token is included in argc.
The redirection token and the TK_CHAR token follows the redirection token
will not be included in argc.
*/
static int	_count_argc(t_token *start, t_token *end)
{
	t_token	*p_token;
	int		argc;

	argc = 0;
	p_token = start;
	while (p_token != end)
	{
		if (p_token->tk == TK_CHAR)
		{
			p_token = p_token->next;
			argc++;
		}
		else if (_is_valid_redirection_token(p_token))
		{
			p_token = p_token->next->next;
		}
		else
			return (-1);
	}
	return (argc);
}

static char	**_aquire_argv(t_token *start, int argc)
{
	char	**argv;
	t_token	*p_token;
	int		i;

	argv = (char **)ft_calloc(argc + 1, sizeof(char *));
	if (!argv)
		return (NULL);
	i = 0;
	p_token = start;
	while (i < argc)
	{
		if (p_token->tk == TK_CHAR)
		{
			argv[i] = ft_strdup(p_token->data);
			if (argv[i] == NULL)
				return (_free_argv(argv), NULL);
			i++;
			p_token = p_token->next;
		}
		else if (_is_valid_redirection_token(p_token))
		{
			p_token = p_token->next->next;
		}
	}
	return (argv);
}

static void	_free_argv(char **argv)
{
	int	i;

	if (argv == NULL)
		return ;
	while (argv[i] != NULL)
	{
		free(argv[i++]);
	}
	return ;
}

static int	_is_valid_redirection_token(t_token *token)
{
	if (token == NULL)
		return (0);
	if (is_red(token->tk) != 0)
		return (0);
	if (token->next == NULL)
		return (0);
	if (token->next->tk == TK_CHAR)
		return (1);
	else
		return (0);
}
