/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 15:09:57 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/11/20 15:39:49 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define SHELL_ALLOC_FAIL_MSG "Failed to allocate t_shell object."
#define BUF_APP_ALLOC_FAIL_MSG "Failed to allocate t_ms_buf or t_app object."

static t_ms_buf	*_create_input_buffer(void);

/**
 * @brief Create a t shell object. Returns NULL if memory allocation failed.
 *
 * @param argc
 * @param argv
 * @param envp
 * @return t_shell*
 */
t_shell	*create_t_shell(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	shell = (t_shell *)ft_calloc(sizeof(t_shell), 1);
	if (shell == NULL)
	{
		perror(SHELL_ALLOC_FAIL_MSG);
		return (NULL);
	}
	shell->argc = argc;
	shell->argv = argv;
	shell->loglevel = LOGLEVEL;
	shell->status = 0;
	shell->ms_buf = _create_input_buffer();
	shell->app = setup_app(envp, shell);
	if (shell->ms_buf == NULL || shell->app == NULL)
	{
		perror(BUF_APP_ALLOC_FAIL_MSG);
		return (free_shell(shell), NULL);
	}
	return (shell);
}

/**
 * @brief Create t_ms_buf.
 *
 * rl_buf: readline() buffer.
 *
 * tmp_buf: tempolary buffer, used when the command is separated with \newline.
 *
 * sh_buf: buffer passed to execute_shell().
 *
 * @return t_ms_buf* (NULL if malloc failed.)
 */
static t_ms_buf	*_create_input_buffer(void)
{
	t_ms_buf	*ms_buf;

	ms_buf = (t_ms_buf *)malloc(sizeof(t_ms_buf));
	if (ms_buf == NULL)
		return (NULL);
	ft_memset(ms_buf, '\0', sizeof(t_ms_buf));
	ms_buf->rl_buf = NULL;
	ms_buf->tmp_buf = NULL;
	ms_buf->sh_buf = NULL;
	return (ms_buf);
}
