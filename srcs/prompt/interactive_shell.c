/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_shell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 01:59:40 by marvin            #+#    #+#             */
/*   Updated: 2025/10/17 05:42:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>


int	execute_cmd(char *input, t_loglevel log_level)
{
	log_debug_show_input(input, log_level);
	return (0);
}

int	interactive_shell(int argc, char **argv, t_loglevel log_level)
{
	t_ms_buf			*ms_buf;

	log_debug("MINISHELL INTERACTIVE MODE", log_level);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	(void)argc;
	(void)argv;
	ms_buf = create_ms_buf();
	if (ms_buf == NULL)
		return (1);
	while (g_sig_received == 0)
	{
		log_debug_ms_buf(ms_buf, log_level);
		ms_buf->rl_buf = readline(FT_PROMPT);
		if (ms_buf->tmp_buf != NULL && ms_buf->rl_buf == NULL)
		{
			log_debug("1. ms_buf->tmp_buf != NULL && ms_buf->rl_buf == NULL", log_level);
			ms_buf->sh_buf = ft_strdup(ms_buf->tmp_buf);
			if (ms_buf->sh_buf == NULL)
				return (delete_ms_buf(ms_buf), 1);
			free(ms_buf->tmp_buf);
			ms_buf->tmp_buf = NULL;
			execute_cmd(ms_buf->sh_buf, log_level);
			free(ms_buf->sh_buf);
			ms_buf->sh_buf = NULL;
		}
		else if (ms_buf->tmp_buf != NULL && ms_buf->rl_buf != NULL)
		{
			log_debug("2. ms_buf->tmp_buf != NULL && ms_buf->rl_buf != NULL", log_level);
			ms_buf->sh_buf = ft_strjoin(ms_buf->tmp_buf, ms_buf->rl_buf);
			if (ms_buf->sh_buf == NULL)
				return (delete_ms_buf(ms_buf), 1);
			add_history(ms_buf->rl_buf);
			free(ms_buf->rl_buf);
			free(ms_buf->tmp_buf);
			ms_buf->rl_buf = NULL;
			ms_buf->tmp_buf = NULL;
			if (ft_strlen(ms_buf->sh_buf) != 0 && ms_buf->sh_buf[ft_strlen(ms_buf->sh_buf) - 1] == '\\')
			{
				log_debug("2-1. A backslash is found at the end of input.", log_level);
				ms_buf->tmp_buf = ft_strtrim(ms_buf->sh_buf, "\\");
				if (ms_buf->tmp_buf == NULL)
					return (delete_ms_buf(ms_buf), 1);
				free(ms_buf->sh_buf);
				ms_buf->sh_buf = NULL;
				continue;
			}
			execute_cmd(ms_buf->sh_buf, log_level);
			free(ms_buf->sh_buf);
			ms_buf->sh_buf = NULL;
		}
		else if (ms_buf->tmp_buf == NULL && ms_buf->rl_buf == NULL)
		{
			log_debug("3. ms_buf->tmp_buf == NULL && ms_buf->rl_buf == NULL", log_level);
			exit_with_sigeof();
			break ;
		}
		else if (ms_buf->tmp_buf == NULL && ms_buf->rl_buf != NULL)
		{
			log_debug("4. ms_buf->tmp_buf == NULL && ms_buf->rl_buf != NULL", log_level);
			if (ft_strlen(ms_buf->rl_buf) != 0 && ms_buf->rl_buf[ft_strlen(ms_buf->rl_buf) - 1] == '\\')
			{
				log_debug("4-1. A backslash is found at the end of input.", log_level);
				add_history(ms_buf->rl_buf);
				ms_buf->tmp_buf = ft_strtrim(ms_buf->rl_buf, "\\");
				if (ms_buf->tmp_buf == NULL)
					return (delete_ms_buf(ms_buf), 1);
				free(ms_buf->rl_buf);
				ms_buf->rl_buf = NULL;
				continue;
			}
			log_debug("4-2. Executing rl_input", log_level);
			execute_cmd(ms_buf->rl_buf, log_level);
			add_history(ms_buf->rl_buf);
			//free(ms_buf->rl_buf);
			ms_buf->rl_buf = NULL;
		}
	}
	log_debug("5. EXIT", log_level);
	rl_clear_history();
	return (delete_ms_buf(ms_buf), 0);
}
