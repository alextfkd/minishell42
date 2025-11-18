NAME = minishell
CC = cc -g -DLOGLEVEL=0
GCC = gcc -g -DLOGLEVEL=0

OBJDIR = objs
SRCDIR = srcs
UTILS_DIR = utils
PROMT_DIR = prompt
EXEC_DIR = exec
LEXER_DIR = lexer
SHELL_DIR = shell
PARSER_DIR = parser
BUILTIN_DIR = builtin
INCLUDE = includes
HEADER = $(INCLUDE)/exec.h $(INCLUDE)/lexer.h $(INCLUDE)/minishell.h
LIBFT = ./libft/libft.a

CFLAGS = -Wall -Wextra -Werror
IFLAGS = -Iincludes -Ilibft/includes
LFLAGS = -Llibft
LIBFLAGS = -lft -lreadline

MAIN_FILE = main.c
UTILS_FILES = ft_log.c ft_sig_handler.c ft_log_token.c ft_app.c ft_log_astree.c ft_log_astree_sub.c ft_env_conv.c ft_env_mng.c ft_env_list.c

PROMPT_FILES = interactive_shell.c noninteractive_shell.c execute_line.c

LEXER_FILES = extract_symbol_token.c extract_word_token.c lexer.c tokenizer_utils.c

PARSER_FILES = astree.c parser.c param_expansion.c tokens2cmd.c cmd_args.c cmd_redirection.c redirect_utils.c 

SHELL_FILES = ft_shell.c shell_free.c ft_log_shell.c

EXEC_FILES = find_cmd_path.c command.c command_1.c pipeline.c pipeline_1.c redirect_io.c redirect_in.c redirect_out.c heredoc.c heredoc_1.c builtin_cmd.c

BUILTIN_FILES = ft_pwd.c ft_env.c ft_export.c ft_unset.c ft_export_util.c


FILES = $(MAIN_FILE)
FILES += $(addprefix $(UTILS_DIR)/,$(UTILS_FILES))
FILES += $(addprefix $(PROMT_DIR)/,$(PROMPT_FILES))
FILES += $(addprefix $(EXEC_DIR)/,$(EXEC_FILES))
FILES += $(addprefix $(SHELL_DIR)/,$(SHELL_FILES))
FILES += $(addprefix $(LEXER_DIR)/,$(LEXER_FILES))
FILES += $(addprefix $(PARSER_DIR)/,$(PARSER_FILES))
FILES += $(addprefix $(BUILTIN_DIR)/,$(BUILTIN_FILES))
SRCS = $(addprefix $(SRCDIR)/, $(FILES))
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o,$(SRCS))


all: $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(NAME): $(LIBFT) $(OBJS)
	$(GCC) $(CFLAGS) $(IFLAGS) $(OBJS) -o $@ $(LFLAGS) $(LIBFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADER) | $(OBJDIR)
	@mkdir -p $(@D)
	$(GCC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(LIBFT):
	@make --directory ./libft/

libft_clean:
	@make --directory ./libft/ clean

lexer_test: $(LIBFT) $(OBJS)
	$(GCC) $(CFLAGS) $(IFLAGS) -c test/lexer_test.c -o objs/lexer_test.o
	$(GCC) $(CFLAGS) $(IFLAGS) $(filter-out objs/main.o, $(OBJS)) objs/lexer_test.o -o $@ $(LFLAGS) $(LIBFLAGS)

clean: libft_clean
	@rm -f $(OBJS)
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME) ./libft/libft.a

re: fclean all

norminette:
	bash ./norm.sh

.PHONY: all clean fclean re bonus libft norminette

#norminette ./srcs ./includes ./libft
