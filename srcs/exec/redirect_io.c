/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 21:41:31 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/31 21:56:00 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// << <
static int do_redirect_in(t_red *red)
{
    int fd;

    if (red->tk == TK_RED_IN) // <
    {
        fd = open(red->file, O_RDONLY);
        if (fd == -1)
        {
            perror(red->file);
            return (1);
        }
    }
    else if (red->tk == TK_RED_HEREDOC) // <<
    {
        printf("heredoc");
        // fd = open(red->file, O_RDONLY);
        // if (fd == -1)
        // {
        //     perror(red->file);
        //     return (1);
        // }
        return (0);
    }
    else
    {
        return (1);
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
    return (0);
}

// >> >
static int do_redirect_out(t_red *red)
{
    int fd;

    if (red->tk == TK_RED_OUT)
    {
        fd = open(red->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
        {
            perror(red->file);
            return (1);
        }
    }
    else if (red->tk == TK_RED_APPEND)
    {
        fd = open(red->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1)
        {
            perror(red->file);
            return (1);
        }
    }
    else
    {
        return (1);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    return (0);
}

int handle_redirections(t_red *red_list)
{
    t_red  *current = red_list;
    int status = 0;

    while (current != NULL)
    {
        if (current->tk == TK_RED_IN || current->tk == TK_RED_HEREDOC)
            status = do_redirect_in(current);
        else if (current->tk == TK_RED_OUT || current->tk == TK_RED_APPEND)
            status = do_redirect_out(current);
        if (status != 0)
            return (1);
        current = current->next;
    }
    return (0);
}
