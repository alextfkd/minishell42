/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 15:09:57 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/11/18 02:40:07 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ms_buf	*_create_input_buffer(void);

t_shell	*create_t_shell(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	shell = (t_shell *)ft_calloc(sizeof(t_shell), 1);
	if (shell == NULL)
	{
		perror("Failed to allocate t_shell object.");
		return (NULL);
	}
	shell->ms_buf = _create_input_buffer();
	if (shell->ms_buf == NULL)
	{
		return (free(shell), NULL);
	}
	shell->argc = argc;
	shell->argv = argv;
	shell->loglevel = LOGLEVEL;
	shell->status = 0;
	shell->app = setup_app(envp, &(shell->status));
	if (shell->app == NULL)
		return (NULL);
	return (shell);
}

// Create t_ms_buf
// rl_buf: readline() buffer.
// tmp_buf: tempolary buffer, used when the command is separated with \newline.
// sh_buf: buffer passed to execute_shell().
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
