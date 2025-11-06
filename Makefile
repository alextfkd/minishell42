NAME = minishell
CC = cc -g -DLOGLEVEL=0
GCC = gcc -g -DLOGLEVEL=0

OBJDIR = objs
SRCDIR = srcs
UTILS_DIR = utils
PROMT_DIR = prompt
EXEC_DIR = exec
LEXER_DIR = lexer
BUILTIN_DIR = builtin
INCLUDE = includes
HEADER = $(INCLUDE)/exec.h $(INCLUDE)/lexer.h $(INCLUDE)/minishell.h
LIBFT = ./libft/libft.a

CFLAGS = -Wall -Wextra -Werror
IFLAGS = -Iincludes -Ilibft/includes
LFLAGS = -Llibft
LIBFLAGS = -lft -lreadline

SRCS_MAIN = main.c
UTILS_FILES = ft_log.c ft_shell.c ft_sig_handler.c ft_log_token.c ft_app.c ft_log_astree.c ft_log_astree_sub.c
PROMPT_FILES = interactive_shell.c noninteractive_shell.c shell_buffer.c shell_buf_free.c execute_line.c
EXEC_FILES = find_cmd_path.c command.c command_1.c pipeline.c pipeline_1.c redirect_io.c redirect_in.c redirect_out.c heredoc.c heredoc_1.c
LEXER_FILES = extract_symbol_token.c extract_word_token.c lexer.c astree.c command.c command_1.c parser.c redirect.c redirect_1.c
BUILTIN_FILES = ft_pwd.c ft_env.c

FILES = $(SRCS_MAIN)
FILES += $(addprefix $(UTILS_DIR)/,$(UTILS_FILES))
FILES += $(addprefix $(PROMT_DIR)/,$(PROMPT_FILES))
FILES += $(addprefix $(EXEC_DIR)/,$(EXEC_FILES))
FILES += $(addprefix $(LEXER_DIR)/,$(LEXER_FILES))
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
