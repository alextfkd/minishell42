/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 15:35:22 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/28 02:34:40 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// free redirect lst
void free_redirect_list(t_redirect *head)
{
	t_redirect *tmp;

	if(!head)
		return ;
	while(head != NULL)
	{
		tmp = head;
		head = head->next;
		if(tmp->file)
			free(tmp->file);
	}
	free(tmp);
}

// callback function for ft_lstclear()
void	free_cmd_content(void *cmd_ptr)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)cmd_ptr;
	if (!cmd)
		return ;
	if(cmd->red)
		free_redirect_list(cmd->red);
	if (cmd->argv)
		ft_free_tab(cmd->argv);
	free(cmd);
}

// create new t_cmd value
t_cmd	*create_cmd(char *cmd_line)
{
	t_cmd	*cmd;
	char	**argv;
	int		i;

	argv = ft_split(cmd_line, ' ');
	if (!argv || !argv[0])
		return (NULL);
	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
	{
		ft_free_tab(argv);
		return (NULL);
	}
	cmd->argv = argv;
	cmd->red = NULL;
	i = 0;
	while (argv[i] != 0)
		i++;
	cmd->argc = i;
	return (cmd);
}

static void	_free_lst_and_pipe_cmds(t_list **head, char **pipe_cmds)
{
	if (pipe_cmds)
		ft_free_tab(pipe_cmds);
	if (head)
		ft_lstclear(head, free_cmd_content);
}

static int	_process_cmd_node(t_list **head, char *cmd_str)
{
	t_cmd	*cmd;
	t_list	*new_node;

	cmd = create_cmd(cmd_str);
	if (!cmd)
		return (1);
	new_node = ft_lstnew((void *)cmd);
	if (!new_node)
	{
		free_cmd_content((void *)cmd);
		return (1);
	}
	ft_lstadd_back(head, new_node);
	return (0);
}


static t_cmd *_create_empty_cmd()
{
	t_cmd *cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
	{
		perror("minishell: memory allocated error");
		return (NULL);
	}
	return (cmd);
}

t_list *parse_tokens(t_token *token_head)
{
	t_list	*pipeline_head;
	t_token	*current;
	t_cmd	*current_cmd;
	char	*cleaned_arg;

	pipeline_head = NULL;
	current = token_head;
	current_cmd = _create_empty_cmd();

	if(!current_cmd)
		return (NULL);

	while(current != NULL)
	{
		if (current->tk == TK_SEMI)
		{
			if(current_cmd->argc == 0 && current_cmd->red == NULL)
			{
				ft_lstclear(&pipeline_head, free_cmd_content);
				free_cmd_content((void *)current_cmd);
				return (NULL);
			}
			current = current->next;
		}

	}

	return(pipeline_head);

}

t_list	*parse_input(char *input)
{
	char	**pipe_cmds;
	t_list	*head;
	int		i;

	head = NULL;
	pipe_cmds = ft_split(input, '|');
	if (!pipe_cmds || !pipe_cmds[0])
	{
		ft_free_tab(pipe_cmds);
		return (NULL);
	}
	i = 0;
	while (pipe_cmds[i] != NULL)
	{
		if (_process_cmd_node(&head, pipe_cmds[i]))
		{
			_free_lst_and_pipe_cmds(&head, pipe_cmds);
			return (NULL);
		}
		i++;
	}
	ft_free_tab(pipe_cmds);
	return (head);
}
