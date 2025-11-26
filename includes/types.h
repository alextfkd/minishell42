/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 23:43:03 by htsutsum          #+#    #+#             */
/*   Updated: 2025/11/27 02:51:25 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <sys/types.h>
# include "libft.h"

typedef enum e_loglevel
{
	LOG_DEBUG = 0,
	LOG_WARNING = 1,
	LOG_INFO = 2,
	LOG_QUIET = 3,
}	t_loglevel;

typedef enum e_state
{
	S_NORMAL,
	S_DQUOTE,
	S_SQUOTE,
}	t_state;

// Token kind
typedef enum e_tkind
{
	TK_CHAR,
	TK_PIPE,
	TK_RED_OUT,
	TK_RED_APPEND,
	TK_RED_IN,
	TK_RED_HEREDOC,
	TK_ESCAPED_NL
}	t_tkind;

// AST node
typedef enum e_node
{
	NODE_CMD,
	NODE_PIPE
}	t_node;

// type of a bulitin command
typedef enum e_bultin_type
{
	BT_NOT_BULTIN = 0,
	BT_CD,
	BT_EXPORT,
	BT_UNSET,
	BT_EXIT,
	BT_ECHO,
	BT_PWD,
	BT_ENV
}	t_builtin_type;

typedef struct s_token			t_token;
typedef struct s_lexer			t_lexer;
typedef struct s_shell			t_shell;
typedef struct s_app			t_app;
typedef struct s_red			t_red;
typedef struct s_cmd			t_cmd;
typedef struct s_env			t_env;
typedef struct s_astree			t_astree;
typedef struct s_builtin_map	t_builtin_map;
typedef struct s_builtin_entry	t_builtin_entry;
typedef struct s_exec			t_exec;
typedef int						(*t_builtin_func)(t_app *app, t_cmd *s_cmd);

//  Decomposed into token kind and value only
struct s_token
{
	t_tkind		tk;
	char		*data;
	t_token		*next;
	t_state		state;
};

struct s_lexer
{
	char		*line;
	int			idx;
	t_state		state;
	t_token		*head;
	t_token		*tail;
	int			status;
};

// AST
struct	s_astree
{
	t_node		type;
	t_cmd		*cmd;
	t_astree	*left;
	t_astree	*right;
};

// auxiliary structure of redirection (Singly linked list).
struct	s_red
{
	t_tkind	tk;
	int		fd;
	int		is_quoted;
	char	*file;
	t_red	*next;
};

// single command Structure
struct	s_cmd
{
	int		argc;
	char	**argv;
	t_red	*red;
};

struct s_env
{
	char	*key;
	char	*value;
	t_env	*next;
	int		is_set;
};

struct	s_builtin_map
{
	const char		*name;
	t_builtin_type	type;
};

struct s_builtin_entry
{
	t_builtin_type	type;
	t_builtin_func	func;
};

struct s_exec
{
	t_list	*cmd_list;
	t_list	*current;
	pid_t	*pids;
	int		pipe_fds[2];
	int		prev_fd;
	int		cmd_count;
	int		i;
};

struct	s_app
{
	t_shell	*shell;
	char	**envp;
	t_env	*env_list;
	int		original_stdin;
	int		original_stdout;
};

typedef struct s_ms_buf
{
	char	*rl_buf;
	char	*tmp_buf;
	char	*sh_buf;
}	t_ms_buf;

/*
typedef enum e_shell_status
{
	SHELL_SUCCESS = 0,
}								t_status;
*/

struct	s_shell
{
	int			argc;
	char		**argv;
	t_ms_buf	*ms_buf;
	t_loglevel	loglevel;
	int			status;
	t_app		*app;
};

#endif
