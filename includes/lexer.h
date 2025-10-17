/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 23:28:39 by htsutsum          #+#    #+#             */
/*   Updated: 2025/10/18 01:35:35 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


typedef enum e_state
{
	S_NORMAL,
	S_DQUOTE,
	S_SQUOTE
} t_state;

typedef struct s_lexer
{
	const char *buf;
	int			pos;
	t_state		state;
	t_token		*head;
	t_token		*tail;
}				t_lexer;

// Token kind
typedef enum e_tokenkind
{
	TK_CHAR,
	TK_PIPE,
	TK_REDI_IN,
	TK_REDI_OUT,
	TK_RDEI_HEREDOC,
	TK_REDI_APPENDE
}					t_tokenkind;

//  Decomposed into token kind and value only
typedef struct s_token
{
	t_tokenkind		tk;
	char			*val;
	t_token			*next;
}					t_token;

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


