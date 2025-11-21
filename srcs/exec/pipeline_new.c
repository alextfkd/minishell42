/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 18:35:43 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/21 20:30:34 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static t_list	*_astree2cmdlist(t_astree *node);
static void		free_list(t_list **list);
static void		_execve_exit_error(void);
static int		_set_exit_status(int status);
static void		_execute_child_process(t_cmd *cmd, t_app *app);
static void 	_cleanup_pipeline(t_list *cmd_list, pid_t *pids, int count);

static void	_execute_child_process(t_cmd *cmd, t_app *app)
{
	char	*cmd_path;
	int		red_status;

	red_status = handle_redirections(cmd->red, app);
	if (red_status != 0)
		exit(red_status);
	if (cmd->argv == NULL || cmd->argv[0] == NULL)
		exit(0);
	cmd_path = find_cmd_path(cmd->argv[0]);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
        ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
        ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(127);
	}
	clear_residual_fds();
	if (execve(cmd_path, cmd->argv, app->envp) == -1)
	{
		perror("minishell: execve failed");
		free(cmd_path);
		_execve_exit_error();
	}
}

static void	_execve_exit_error(void)
{
	if (errno == EACCES)
		exit(126);
	else
		exit(127);
}

static int	_set_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

/**
 * @brief Recursively converts a pipeline represented in an Abstract Syntax Tree (AST)
 * into a simple linked list of command structures (t_list).
 * * This function processes nodes of type NODE_PIPE and NODE_CMD. It uses a
 * depth-first approach to traverse the left side (which contains the start of the
 * pipeline) and then appends the command from the right side.
 *
 * @param node
 * @return t_list*
 */
static t_list	*_astree2cmdlist(t_astree *node)
{
	t_list *cmd_list;
	t_list *new_node;

	if(!node)
		return (NULL);
	if (node->type == NODE_PIPE)
	{
		cmd_list = _astree2cmdlist(node->left);
		if(!cmd_list)
			return (NULL);
		if (node->right && node->right->type == NODE_CMD)
		{
			new_node = ft_lstnew(node->right->cmd);
			if (!new_node)
				return(free_list(&cmd_list), NULL);
			ft_lstadd_back(&cmd_list, new_node);
		}
		return (cmd_list);
	}
	else if( node->type == NODE_CMD)
		return (ft_lstnew(node->cmd));
	return (NULL);
}

/**
 * @brief free cmd list
 *
 * @param list
 */
static void	free_list(t_list **list)
{
	t_list *current;
	t_list *next_node;

	if (!list || !*list)
		return;

	current = *list;
	while (current)
	{
		next_node = current->next;
		free(current);
		current = next_node;
	}
	*list = NULL;
}

/**
 * @brief Cleans up a pipeline execution by terminating and waiting for child processes,
 * then freeing allocated memory.
 *
 * @param cmd_list
 * @param pids
 * @param count
 */
static void	_cleanup_pipeline(t_list *cmd_list, pid_t *pids, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		kill(pids[i], SIGTERM);
		waitpid(pids[i], NULL, 0);
		i++;
	}
	free(pids);
	free_list(&cmd_list);
}

/**
 * @brief Executes a sequence of commands connected by pipes.
 *
 * * This function iterates through the AST to create child processes
 * and connects their input/output file descriptors.
 *
 * @param node the AST root node
 * @param app
 * @return int  exit_status of the last command
 *
 *
 */
int execute_pipeline(t_astree *node, t_app *app)
{
	t_list 	*cmd_list;
	t_list 	*current;
	int		prev_fd = STDIN_FILENO;
	int		pipe_fds[2];
	pid_t	*pids;
	int		cmd_count;
	int		i;
	int		last_status;
	int		status;
	int		red_status;
	t_cmd	*cmd;

	last_status = 0;
	cmd_list = _astree2cmdlist(node);
	if (!cmd_list)
		return (1);

	cmd_count = ft_lstsize(cmd_list);
	if (cmd_count == 1)
	{
		cmd = (t_cmd *)cmd_list->content;
		if (get_builtin_type(cmd) != BT_NOT_BULTIN && BUILTIN_ON)
		{
			last_status = execute_builtin_parent(cmd, app);
			free_list(&cmd_list);
			log_debug(ft_itoa(last_status), LOG_DEBUG);
			return (last_status);
		}
	}
	pids = (pid_t *)malloc(sizeof(pid_t) * cmd_count);
	if (!pids)
	{
		perror("minishell: malloc");
		free_list(&cmd_list);
		return (1);
	}
	current = cmd_list;
	i = 0;
	while (current)
	{
		cmd = (t_cmd *)current->content;
		if (current->next != NULL && pipe(pipe_fds) == -1)
		{
			perror("minishell: pipe");
			if (prev_fd != STDIN_FILENO)
				close(prev_fd);
			_cleanup_pipeline(cmd_list, pids, i);
			return (1);
		}

		pids[i] = fork();
		if (pids[i] < 0)
		{
			perror("minishell: fork");
			if (current->next != NULL)
			{
				close(pipe_fds[0]);
				close(pipe_fds[1]);
			}
			if (prev_fd != STDIN_FILENO)
				close(prev_fd);
			_cleanup_pipeline(cmd_list, pids, i);
			return (1);
		}
		if (pids[i] == 0)
		{
			free(pids);
			if (prev_fd != STDIN_FILENO)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (current->next != NULL)
			{
				close(pipe_fds[0]);
				dup2(pipe_fds[1], STDOUT_FILENO);
				close(pipe_fds[1]);
			}
			if (get_builtin_type(cmd) != BT_NOT_BULTIN && BUILTIN_ON)
			{
				red_status = handle_redirections(cmd->red, app);
				if (red_status != 0)
					exit(red_status);
				exit(execute_builtin_cmd(cmd, app));
			}
			else
				_execute_child_process(cmd, app);
		//	exit(1);
		}
		if (prev_fd != STDIN_FILENO)
			close(prev_fd);
		if (current->next != NULL)
		{
			close(pipe_fds[1]);
			prev_fd = pipe_fds[0];
		}
		else
			prev_fd = STDIN_FILENO;

		current = current->next;
		i++;
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	i = 0;
	while (i < cmd_count)
	{
		if (waitpid(pids[i], &status, 0) == -1)
			status = (1 << 8);
		if (i == cmd_count - 1)
			last_status = _set_exit_status(status);
		i++;
	}
	if (app->shell)
        set_sigaction(app->shell);
	free(pids);
	free_list(&cmd_list);
	log_debug(ft_itoa(last_status),LOG_DEBUG);
	return (last_status);
}
