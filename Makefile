NAME = minishell
CC = cc -g
GCC = gcc -g

OBJDIR = ./objs
OBJSUBDIR = ./objs/utils ./objs/prompt ./objs/exec
SRCDIR = ./srcs
INCLUDE = includes
LIBFT = ./libft/libft.a

SRCS = main.c
SRCS += utils/ft_log.c utils/ft_sig_handler.c
SRCS += prompt/interactive_shell.c prompt/noninteractive_shell.c
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
	norminette ./srcs ./includes ./libft

.PHONY: all clean fclean re bonus libft norminette
