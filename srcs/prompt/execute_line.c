/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 09:26:24 by marvin            #+#    #+#             */
/*   Updated: 2025/10/17 09:28:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_line_1(
				t_ms_buf *ms_buf,
				char **envp,
				t_loglevel	log_level,
				int	*status
				);
static void	exec_line_2(
				t_ms_buf *ms_buf,
				char **envp,
				t_loglevel	log_level,
				int	*status
				);
static void	exec_line_3(
				t_ms_buf *ms_buf,
				char **envp,
				t_loglevel	log_level,
				int	*status
				);
static void	exec_line_4(
				t_ms_buf *ms_buf,
				char **envp,
				t_loglevel	log_level,
				int	*status
				);

void	exec_line(
	t_ms_buf *ms_buf, char **envp, t_loglevel log_level, int *status
)
{
	if (ms_buf->tmp_buf != NULL && ms_buf->rl_buf == NULL)
		exec_line_1(ms_buf, envp, log_level, status);
	else if (ms_buf->tmp_buf != NULL && ms_buf->rl_buf != NULL)
		exec_line_2(ms_buf, envp, log_level, status);
	else if (ms_buf->tmp_buf == NULL && ms_buf->rl_buf == NULL)
		exec_line_3(ms_buf, envp, log_level, status);
	else if (ms_buf->tmp_buf == NULL && ms_buf->rl_buf != NULL)
		exec_line_4(ms_buf, envp, log_level, status);
	else
		*status = 1;
}

static void	exec_line_1(
	t_ms_buf *ms_buf, char **envp, t_loglevel log_level, int	*status
)
{
	log_debug("1. tmp_buf != NULL && rl_buf == NULL", log_level);
	ms_buf->sh_buf = ft_strdup(ms_buf->tmp_buf);
	if (ms_buf->sh_buf == NULL)
	{
		*status = 1;
		return ;
	}
	free_tmp_buf(ms_buf);
	*status = execute_cmd(ms_buf->sh_buf, envp, log_level);
	free_shell_buf(ms_buf);
}

static void	exec_line_2(
	t_ms_buf *ms_buf, char **envp, t_loglevel log_level, int	*status
)
{
	log_debug("2. tmp_buf != NULL && rl_buf != NULL", log_level);
	ms_buf->sh_buf = ft_strjoin(ms_buf->tmp_buf, ms_buf->rl_buf);
	if (ms_buf->sh_buf == NULL)
	{
		*status = 1;
		return ;
	}
	add_history(ms_buf->rl_buf);
	free_readline_buf(ms_buf);
	free_tmp_buf(ms_buf);
	if (ft_strlen(ms_buf->sh_buf) != 0 && \
ms_buf->sh_buf[ft_strlen(ms_buf->sh_buf) - 1] == '\\')
	{
		log_debug("2-1. A backslash is found at the end of input.", log_level);
		ms_buf->tmp_buf = ft_strtrim(ms_buf->sh_buf, "\\");
		if (ms_buf->tmp_buf == NULL)
		{
			*status = 1;
			return ;
		}
		return (free_shell_buf(ms_buf));
	}
	*status = execute_cmd(ms_buf->sh_buf, envp, log_level);
	free_shell_buf(ms_buf);
}

static void	exec_line_3(
	t_ms_buf *ms_buf, char **envp, t_loglevel log_level, int	*status
)
{
	log_debug("3. tmp_buf == NULL && rl_buf == NULL", log_level);
	(void)ms_buf;
	(void)envp;
	*status = 0;
	exit_with_sigeof();
}

static void	exec_line_4(
	t_ms_buf *ms_buf, char **envp, t_loglevel log_level, int	*status
)
{
	log_debug("4. tmp_buf == NULL && rl_buf != NULL", log_level);
	if (ft_strlen(ms_buf->rl_buf) != 0 && \
ms_buf->rl_buf[ft_strlen(ms_buf->rl_buf) - 1] == '\\')
	{
		log_debug("4-1. A backslash is found at the end of input.", log_level);
		add_history(ms_buf->rl_buf);
		ms_buf->tmp_buf = ft_strtrim(ms_buf->rl_buf, "\\");
		if (ms_buf->tmp_buf == NULL)
		{
			*status = 1;
			return ;
		}
		free_readline_buf(ms_buf);
		return ;
	}
	log_debug("4-2. Executing rl_input", log_level);
	log_debug(ms_buf->rl_buf, log_level);
	add_history(ms_buf->rl_buf);
	*status = execute_cmd(ms_buf->rl_buf, envp, log_level);
	free_readline_buf(ms_buf);
}
