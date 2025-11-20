/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 18:35:43 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/20 11:06:00 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static t_list	_astree2cmdlist(t_astree *node);
static void	free_list(t_list **list);

static t_list	_astree2cmdlist(t_astree *node);
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
	*lst = NULL;
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
// 既存の _child_routine_cmd, _wait_for_all_children は使用

int execute_pipeline(t_astree *node, t_app *app)
{
    t_list  *cmd_list_head;
    t_list  *current_cmd_node;
    int     prev_fd;
    pid_t   last_pid;
    int     exit_status;

    if (!node) return (0);

    // 1. 【平坦化】 ASTからコマンドリストを作成
    cmd_list_head = _collect_pipeline_cmds_list(node);
    if (!cmd_list_head) return (1);

    // 2. 【反復実行】 リストを辿りながらプロセスを起動
    current_cmd_node = cmd_list_head;
    prev_fd = STDIN_FILENO;
    last_pid = -1;

    while (current_cmd_node)
    {
        t_cmd *current_cmd = (t_cmd *)current_cmd_node->content;

        // 次のノードの存在で最後のコマンドかを判定
        int is_last = (current_cmd_node->next == NULL);
        int pipe_fds[2] = {-1, -1};

        // 最後のコマンドでない場合のみパイプを作成
        if (!is_last && pipe(pipe_fds) == -1)
        {
            /* 🚨 パイプエラー処理: すでに起動した子プロセスの回収が必要 */
            if (prev_fd != STDIN_FILENO) close(prev_fd);
            // waitpid(-1) ループで全ての子を回収し、クリーンアップへ
            _wait_for_all_children(-1);
            // 💡 クリーンアップとエラーリターン (3.へジャンプする)
            goto cleanup_and_exit;
        }

        last_pid = fork();
        if (last_pid == -1)
        {
            /* 🚨 forkエラー処理 */
            if (prev_fd != STDIN_FILENO) close(prev_fd);
            if (!is_last) { close(pipe_fds[0]); close(pipe_fds[1]); }
            _wait_for_all_children(-1);
            // 💡 クリーンアップとエラーリターン (3.へジャンプする)
            goto cleanup_and_exit;
        }

        if (last_pid == 0) // 子プロセス
        {
            if (!is_last) close(pipe_fds[0]);
            _child_routine_cmd(current_cmd, app,
                prev_fd, is_last ? STDOUT_FILENO : pipe_fds[1]);
        }

        // 親プロセス
        if (prev_fd != STDIN_FILENO) close(prev_fd);

        if (!is_last)
        {
            close(pipe_fds[1]); // 書き込み口を閉じる
            prev_fd = pipe_fds[0]; // 次のループのために読み取り口を設定
        }

        current_cmd_node = current_cmd_node->next;
    }

    // 3. 正常終了時のクリーンアップ
    exit_status = _wait_for_all_children(last_pid); // 待機とステータス取得

    // 4. クリーンアップと終了
cleanup_and_exit:

    // 最後に残った読み取りFDを閉じる
    if (prev_fd != STDIN_FILENO) close(prev_fd);

    // AST全体をクリア (t_cmd の解放を含む)
    astree_clear(node);

    // リスト構造体のみを解放 (t_cmd は解放しない)
    free_list(&cmd_list_head);

    return (exit_status);
}


// int	execute_pipeline(t_astree *node, t_app *app)
// {
// 	int         prev_fd;
// 	t_astree    *last_node;
// 	pid_t       last_pid;

// 	if (!node)
// 		return (0);
// 	prev_fd = STDIN_FILENO;
// 	last_node = _run_pipe_routine(node, app, &prev_fd);
// 	if (!last_node && prev_fd != STDIN_FILENO)
// 	{
// 		close(prev_fd);
// 		return (1);
// 	}
// 	last_pid = fork();
// 	if (last_pid == 0)
// 		_child_routine(last_node, app, prev_fd, STDOUT_FILENO);
// 	if (prev_fd != STDIN_FILENO)
// 		close(prev_fd);
// 	return (_wait_pipeline(last_pid));
// }

// static t_astree *_run_pipe_routine(t_astree *current, t_app *app, int *prev_fd)
// {
// 	int		fds[2];
// 	pid_t	pid;

// 	while (current && current->type == NODE_PIPE)
// 	{
// 		if (pipe(fds) == -1)
// 			return (NULL);
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			close(fds[0]);
// 			_child_routine(current->right, app, *prev_fd, fds[1]);
// 		}
// 		close(fds[1]);
// 		if (*prev_fd != STDIN_FILENO)
// 			close(*prev_fd);
// 		*prev_fd = fds[0];
// 		current = current->;
// 	}
// 	return (current);
// }

// static void	_child_routine(t_astree *node, t_app *app, int in_fd, int out_fd)
// {
// 	if (in_fd != STDIN_FILENO)
// 	{
// 		dup2(in_fd, STDIN_FILENO);
// 		close(in_fd);
// 	}
// 	if (out_fd != STDOUT_FILENO)
// 	{
// 		dup2(out_fd, STDOUT_FILENO);
// 		close(out_fd);
// 	}
// 	if (node->type == NODE_CMD)
// 		execute_single_cmd(node->cmd, app);
// 	exit(1);
// }
