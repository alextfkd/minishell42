/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:50:00 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/18 16:50:34 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "./libft/includes/libft.h"
# include "lexer.h"
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define MAX_CMD 100
# define CMD_NOT_FOUND 127

typedef struct s_redirection	t_redirection;
typedef struct s_pipeline		t_pipeline;

// Auxiliary structure of redirection
typedef struct s_redirection
{
	t_tokenkind					tk;
	char						*file;
	t_redirection				*next;
}								t_redirection;

// Single command Structure
typedef struct s_cmd
{
	int							ac;
	char						**av;
	char						**ep;
	t_redirection				*red;
}								t_cmd;

// The entire pipline
typedef struct s_pipeline
{
	t_cmd						*cmd;
	t_pipeline					*next;
}								t_pipeline;

int								exec_cmd(char *input, char **ep);
int								exec_shell_cmd(t_cmd *cmd, char **ep);
char							*find_cmd_path(char *av0);

#endif
