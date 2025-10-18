/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:50:00 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/18 12:24:42 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "lexer.h"

# define MAX_CMD 100

typedef struct s_redirection	t_redirection;
typedef struct s_pipeline		t_pipeline;

// Auxiliary structure of redirection
typedef struct s_redirection
{
	t_tokenkind		tk;
	char			*file;
	t_redirection	*next;
}					t_redirection;

// Single command Structure
typedef struct s_cmd
{
	int				ac;
	char			**av;
	char			**ep;
	t_redirection	*red;
}					t_cmd;

// The entire pipline
typedef struct s_pipeline
{
	t_cmd			*cmd;
	t_pipeline		*next;
}					t_pipeline;

int		exec_command(char *input, char **ep);

#endif
