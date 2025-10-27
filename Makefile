NAME = minishell
CC = cc -g
GCC = gcc -g

OBJDIR = ./objs
OBJSUBDIR = ./objs/utils ./objs/prompt ./objs/exec
SRCDIR = ./srcs
INCLUDE = includes
LIBFT = ./libft/libft.a

SRCS = main.c
SRCS += utils/ft_log.c utils/ft_sig_handler.c utils/ft_log_token.c
SRCS += prompt/interactive_shell.c prompt/noninteractive_shell.c prompt/shell_buffer.c prompt/shell_buf_free.c prompt/execute_line.c
SRCS += exec/exec_single_cmd.c exec/exec_pipline.c exec/exec_pipline_util.c exec/parse_input.c exec/find_cmd_path.c exec/exec_bultin_cmd_in_parent.c
SRCS += lexer/extract_symbol_token.c lexer/extract_word_token.c lexer/lexer.c
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

CFLAGS = -Wall -Wextra -Werror
IFLAGS = -Iincludes -Ilibft/includes
LFLAGS = -Llibft
LIBFLAGS = -lft -lreadline

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(NAME): $(LIBFT) $(OBJS)
	$(GCC) $(CFLAGS) $(IFLAGS) $(OBJS) -o $@ $(LFLAGS) $(LIBFLAGS)

$(OBJDIR)/main.o: $(SRCDIR)/main.c
	$(GCC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(OBJDIR)/utils/%.o: $(SRCDIR)/utils/%.c
	mkdir -p $(OBJDIR)/utils
	$(GCC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(OBJDIR)/prompt/%.o: $(SRCDIR)/prompt/%.c
	mkdir -p $(OBJDIR)/prompt
	$(GCC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(OBJDIR)/exec/%.o: $(SRCDIR)/exec/%.c
	mkdir -p $(OBJDIR)/exec
	$(GCC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(OBJDIR)/lexer/%.o: $(SRCDIR)/lexer/%.c
	mkdir -p $(OBJDIR)/lexer
	$(GCC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(LIBFT):
	make --directory ./libft/

libft_clean:
	make --directory ./libft/ clean

clean: libft_clean
	rm -f $(OBJS)
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME) ./libft/libft.a

re: fclean all

norminette:
	bash ./norm.sh

.PHONY: all clean fclean re bonus libft norminette

#norminette ./srcs ./includes ./libft
