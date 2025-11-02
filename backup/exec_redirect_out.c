/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect_out.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 21:41:31 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/31 13:33:19 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <fcntl.h>
#include <unistd.h>


void setup_out()
{
    return;
}

void setup_append()
{

}


int handle_input_redirection(t_red *red_node)
{
    int fd;

    if (red_node->tk == TK_RED_HEREDOC)
    {
        // TK_RED_HEREDOC の処理:
        // 1. ヒアドキュメントのコンテンツを一時ファイルに書き込む処理 (別の関数が必要)
        // 2. その一時ファイルを開く
        // 現時点では、一時ファイルを開く処理を想定します。
        // fd = open_heredoc_tmp_file(red_node->data);
        fd = open(red_node->data, O_RDONLY); // 暫定的にファイル名として扱う
    }
    else // TK_RED_IN (< file)
    {
        fd = open(red_node->data, O_RDONLY);
    }

    if (fd == -1)
    {
        perror(red_node->data); // 'file' name
        return (1);
    }

    // FD 0 を開いたファイルに繋ぎ替え
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        perror("minishell: dup2 input error");
        close(fd);
        return (1);
    }
    close(fd);
    return (0);
}
#include <fcntl.h>
#include <unistd.h>


/**
 * @brief 標準出力 (FD 1) へのリダイレクトを処理する。
 * @param red_node TK_RED_OUT または TK_RED_APPEND ノード
 * @return int 成功時: 0, 失敗時: 1
 */
int handle_output_redirection(t_red *red_node)
{
    int fd;
    int flags;

    if (red_node->tk == TK_RED_OUT)
        flags = O_WRONLY | O_CREAT | O_TRUNC; // > (上書き)
    else // TK_RED_APPEND (>> append)
        flags = O_WRONLY | O_CREAT | O_APPEND; // >> (追記)

    // 0644 はファイル権限 (rw-r--r--)
    fd = open(red_node->data, flags, 0644);

    if (fd == -1)
    {
        perror(red_node->data);
        return (1);
    }

    // FD 1 を開いたファイルに繋ぎ替え
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("minishell: dup2 output error");
        close(fd);
        return (1);
    }
    close(fd);
    return (0);
}



int	exec_redirect_out(t_redirect *red)
{
	t_redirect	*current;
	int			fd;
	int			last_fd_opened;

	last_fd_opened = -1;
	current = red;
	while (current != NULL)
	{
		if (last_fd_opened != -1)
			close(last_fd_opened);
		if (current->tk == TK_REDI_OUT_TRUC)
			fd = open(current->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (current->tk == TK_REDI_OUT_APPEND)
			fd = open(current->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
		{
			current = current->next;
			continue ;
		}
		if (fd == -1)
		{
			perror("minishell: open error");
			return (1);
		}
		last_fd_opened = fd;
		current = current->next;
	}
	if (last_fd_opened != -1)
	{
		if (dup2(last_fd_opened, STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2 error");
			close(last_fd_opened);
			return (1);
		}
		close(last_fd_opened);
	}
	return (0);
}
