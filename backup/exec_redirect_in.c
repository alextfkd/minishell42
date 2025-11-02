/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 21:41:31 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/31 13:59:13 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>



void setup_in(t_red *red,t_app)
{
    if(red->tk == TK_RED_IN)
        set_up_red_in(t_red);
    else if(red->tk == TK_RED_HEREDOC)
        setup_heredoc(red)
    red = re->next;
}

void setup_heredoc(red)
{
    int fd;

    fd = open(red->data, O_RDONLY);
    if(fd == -1)
    {
        perror(re->data)
        exit(2);
    }
    dup2(fd,STDIN_FILENO);
}
/**
 * @brief 標準入力 (FD 0) へのリダイレクトを処理する。
 * @param red_node TK_RED_IN または TK_RED_HEREDOC ノード
 * @return int 成功時: 0, 失敗時: 1
 */
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



#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <readline/readline.h> // 💡 readlineヘッダーファイル

// ⚠️ 注意: expand_variables関数の実装は省略します。
// 実際のminishellでは、環境変数を参照して展開するロジックが必要です。
char *expand_variables(const char *line)
{
    // ... 変数展開ロジックの実装 ...

    // 展開処理がないと仮定し、ここでは元の文字列を複製して返す (改行は含めない)
    // 実際には、展開後の文字列をmallocして返す
    return strdup(line);
}

/**
 * @brief ヒアドキュメントの入力処理を行い、パイプを通してデータを渡す。
 * readlineを使用して入力を受け付ける。
 * @param delimiter リミッター文字列（引用符は除去済み）。
 * @param should_expand 1であれば行に対して変数展開を行う、0であれば行をリテラルとして扱う。
 * @return int 成功時はパイプの読み込み端FD、失敗時は-1。
 */
int handle_heredoc(const char *delimiter, int should_expand)
{
    int     pipe_fds[2];
    char    *line;
    char    *line_with_newline; // パイプに書き込むために改行を追加した行
    char    *content_to_write;  // 展開後、または元の行（改行付き）
    size_t  delimiter_len;
	size_t	content_to_write_len;

    if (pipe(pipe_fds) == -1)
    {
        perror("minishell: pipe failed for heredoc");
        return (-1);
    }

    delimiter_len = strlen(delimiter);

    while (1)
    {
        // 💡 readlineを使用して入力を受け付ける
        // プロンプトは標準的なヒアドキュメントのプロンプトである "> " を使用
        line = readline("> ");

        // 1. EOF (Ctrl+D) または読み取りエラーのチェック
        if (line == NULL)
        {
            // EOFに到達した場合、警告などを表示しても良い
            fprintf(stderr, "minishell: warning: here-document delimited by end-of-file (wanted `%s`)\n", delimiter);
            break;
        }

        // 2. デリミタチェック
        if (strcmp(line, delimiter) == 0)
        {
            free(line);
            break; // リミッターに到達
        }

        // 3. 展開処理の分岐
        if (should_expand)
        {
            // 展開が必要な場合：行を変数展開する
            // 💡 expand_variablesは改行を含まない文字列を処理すると仮定
            content_to_write = expand_variables(line);
        }
        else
        {
            // 展開が不要な場合：元の行をそのまま使用する
            // lineはmallocされた文字列なので、解放するためにここではdupする（または下の解放ロジックを変更）
            content_to_write = strdup(line);
        }

        // 4. パイプへの書き込み (readlineは改行文字を返さないため、手動で追加する)
        // line_with_newlineのメモリを確保
        line_with_newline = malloc(ft_strlen(content_to_write) + 2); // +2 for '\n' and '\0'
        if (!line_with_newline)
        {
             perror("minishell: malloc failed");
             free(line);
             free(content_to_write);
             close(pipe_fds[0]);
             close(pipe_fds[1]);
             return (-1);
        }
		content_to_write_len = ft_strlen(content_to_write);
    	ft_stlcpy(line_with_newline, content_to_write_len + 2);
		line_with_newline[content_to_write_len] = '\n';
		line_with_newline[content_to_write_len + 1] = '\0';

        if (write(pipe_fds[1], line_with_newline, strlen(line_with_newline)) == -1)
        {
            perror("minishell: write to pipe failed");
            free(line);
            free(content_to_write);
            free(line_with_newline);
            close(pipe_fds[0]);
            close(pipe_fds[1]);
            return (-1);
        }

        // 5. メモリの解放
        free(line); // readlineでmallocされた行を解放
        free(content_to_write); // 展開後/dupされた文字列を解放
        free(line_with_newline); // パイプ書き込み用文字列を解放
    }

    close(pipe_fds[1]); // 書き込みを終了
    return (pipe_fds[0]); // 読み込み端を返す
}

int exec_redirection_in(t_redirect *red)
{
    t_redirect  *current;
    int         fd;
    int         last_fd_opened = -1;

    current = red;
    while (current != NULL)
    {
        // 既に開いているFDがあれば閉じる (最後の有効なリダイレクトが適用されるため)
        if (last_fd_opened != -1)
        {
            close(last_fd_opened);
            last_fd_opened = -1;
        }

        if (current->tk == TK_REDI_IN_FILE)
        {
            // ファイルからの入力 (<)
            fd = open(current->file, O_RDONLY);
            if (fd == -1)
            {
                perror("minishell: open error");
                return (-1);
            }
            last_fd_opened = fd;
        }
        else if (current->tk == TK_REDI_IN_HEREDOC)
        {
            // ヒアドキュメント (<<)
            // handle_heredocはパイプの読み込み端FDを返す
            fd = handle_heredoc(current->file,0); // current->file はデリミタ文字列
            if (fd == -1)
            {
                // handle_heredoc内でエラー処理済み
                return (-1);
            }
            last_fd_opened = fd;
        }

        current = current->next;
    }

    // 最後の有効なファイルディスクリプタを標準入力(0)に複製
    if (last_fd_opened != -1)
    {
        if (dup2(last_fd_opened, STDIN_FILENO) == -1)
        {
            perror("minishell: dup2 error");
            close(last_fd_opened);
            return (-1);
        }
        close(last_fd_opened); // 複製元は閉じる
    }
    return (0);
}
