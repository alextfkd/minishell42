NAME = minishell
CC = cc -g -DLOGLEVEL=0
GCC = gcc -g -DLOGLEVEL=0

OBJDIR = objs
SRCDIR = srcs
UTILS_DIR = utils
PROMT_DIR = prompt
EXEC_DIR = exec
LEXER_DIR = lexer
EXPANSION_DIR = expansion
SIGNAL_DIR = signal
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
BUILTINFLAGS = -DBUILTIN_ON=1

MAIN_FILE = main.c

UTILS_FILES = ft_log.c ft_log_token.c ft_app.c ft_log_astree.c ft_log_astree_sub.c ft_env_conv.c ft_env_mng.c ft_env_list.c

SIGNAL_FILES = sig_handler.c sigaction.c

PROMPT_FILES = interactive_shell.c noninteractive_shell.c pipeline_executor.c integrate_input_buffer.c

LEXER_FILES = extract_symbol_token.c extract_word_token.c lexer.c tokenizer_utils.c

EXPANSION_FILES = param_expansion.c

PARSER_FILES = astree.c parser.c tokens2cmd.c cmd_args.c cmd_redirection.c redirect_utils.c

SHELL_FILES = ft_shell.c shell_free.c ft_log_shell.c

EXEC_FILES = find_cmd_path.c pipeline_new.c command_1.c redirect_io.c redirect_in.c redirect_out.c heredoc.c heredoc_util.c builtin_cmd.c

BUILTIN_FILES = ft_pwd.c ft_env.c ft_export.c ft_cd.c ft_echo.c ft_exit.c ft_unset.c ft_export_util.c

FILES = $(MAIN_FILE)
FILES += $(addprefix $(UTILS_DIR)/,$(UTILS_FILES))
FILES += $(addprefix $(PROMT_DIR)/,$(PROMPT_FILES))
FILES += $(addprefix $(SIGNAL_DIR)/,$(SIGNAL_FILES))
FILES += $(addprefix $(EXEC_DIR)/,$(EXEC_FILES))
FILES += $(addprefix $(EXPANSION_DIR)/,$(EXPANSION_FILES))
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

lexer_test: $(LIBFT) $(OBJS)
	$(GCC) $(CFLAGS) $(IFLAGS) -c test/lexer_test.c -o objs/lexer_test.o
	$(GCC) $(CFLAGS) $(IFLAGS) $(filter-out objs/main.o, $(OBJS)) objs/lexer_test.o -o $@ $(LFLAGS) $(LIBFLAGS)

parser_test: $(LIBFT) $(OBJS)
	$(GCC) $(CFLAGS) $(IFLAGS) -c test/parser_test.c -o objs/parser_test.o
	$(GCC) $(CFLAGS) $(IFLAGS) $(filter-out objs/main.o, $(OBJS)) objs/parser_test.o -o $@ $(LFLAGS) $(LIBFLAGS)

expansion_test: $(LIBFT) $(OBJS)
	$(GCC) $(CFLAGS) $(IFLAGS) -c test/expansion_test.c -o objs/expansion_test.o
	$(GCC) $(CFLAGS) $(IFLAGS) $(filter-out objs/main.o, $(OBJS)) objs/expansion_test.o -o $@ $(LFLAGS) $(LIBFLAGS)

builtin: fclean
	$(MAKE) CFLAGS="$(CFLAGS) $(BUILTINFLAGS)" all

$(LIBFT):
	@make --directory ./libft/

libft_clean:
	@make --directory ./libft/ clean

clean: libft_clean
	@rm -f $(OBJS)
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME) ./libft/libft.a

re: fclean all

norminette:
	bash ./norm.sh

.PHONY: all clean fclean re bonus norminette lexer_test builtin

#norminette ./srcs ./includes ./libft
