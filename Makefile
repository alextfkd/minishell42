NAME = minishell
CC = cc -g -DLOGLEVEL=0
GCC = gcc -g -DLOGLEVEL=0

OBJDIR = objs
SRCDIR = srcs
UTILSDIR = utils
PROMTDIR = prompt
EXECDIR = exec
LEXERDIR = lexer
INCLUDE = includes
HEADER = $(INCLUDE)/exec.h $(INCLUDE)/lexer.h $(INCLUDE)/minishell.h
LIBFT = ./libft/libft.a

CFLAGS = -Wall -Wextra -Werror
IFLAGS = -Iincludes -Ilibft/includes
LFLAGS = -Llibft
LIBFLAGS = -lft -lreadline

SRCS_MAIN = main.c
UTILS_FILES = ft_log.c ft_shell.c ft_sig_handler.c ft_log_token.c ft_app.c ft_log_astree.c
PROMPT_FILES = interactive_shell.c noninteractive_shell.c shell_buffer.c shell_buf_free.c execute_line.c
EXEC_FILES = find_cmd_path.c command.c cmd_args.c pipeline.c pipeline_1.c redirect_io.c redirect_in.c redirect_out.c heredoc.c heredoc_1.c
LEXER_FILES = extract_symbol_token.c extract_word_token.c lexer.c astree.c command.c cmd_args.c parser.c cmd_redirection.c redirect_utils.c tokenizer_utils.c

FILES = $(SRCS_MAIN)
FILES += $(addprefix $(UTILSDIR)/,$(UTILS_FILES))
FILES += $(addprefix $(PROMTDIR)/,$(PROMPT_FILES))
FILES += $(addprefix $(EXECDIR)/,$(EXEC_FILES))
FILES += $(addprefix $(LEXERDIR)/,$(LEXER_FILES))
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
