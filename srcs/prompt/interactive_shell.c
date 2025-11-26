/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_shell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 01:59:40 by marvin            #+#    #+#             */
/*   Updated: 2025/11/26 21:26:46 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*readline_with_nl(char *prompt1, char *prompt2, t_shell *shell);
static int	_is_eof(t_ms_buf *t_ms_buf);

int	interactive_shell(t_shell *shell)
{
	t_ms_buf			*ms_buf;

	log_debug("MINISHELL INTERACTIVE MODE", shell->loglevel);
	set_sigaction(shell);
	ms_buf = shell->ms_buf;
	while (1)
	{
		log_debug_ms_buf(shell);
		ms_buf->rl_buf = readline_with_nl(FT_PROMPT, ">", shell);
		if (g_sig_received == 2)
			shell->status = 130;
		if (_is_eof(ms_buf))
		{
			free_readline_buf(ms_buf);
			break ;
		}
		ms_buf->sh_buf = integrate_input_buffer(shell);
		if (ms_buf->sh_buf)
			pipeline_executor(shell);
		else
			continue ;
	}
	write(1, "exit\n", 5);
	rl_clear_history();
	return (shell->status);
}

static char	*readline_with_nl(char *prompt1, char *prompt2, t_shell *shell)
{
	t_ms_buf	*ms_buf;
	char		*buf;
	char		*tmp;

	ms_buf = shell->ms_buf;
	if (ms_buf->tmp_buf == NULL)
		tmp = readline(prompt1);
	else
		tmp = readline(prompt2);
	if (tmp == NULL)
	{
		shell->status = 1;
		return (NULL);
	}
	add_history(tmp);
	buf = ft_strjoin(tmp, "\n");
	free (tmp);
	if (buf == NULL)
	{
		shell->status = 1;
		return (NULL);
	}
	return (buf);
}

static int	_is_eof(t_ms_buf *t_ms_buf)
{
	if (!t_ms_buf)
		return (-1);
	if (!(t_ms_buf->rl_buf))
		return (1);
	return (0);
}
