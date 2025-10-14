NAME = minishell
CC = cc -g
GCC = gcc -g

OBJDIR = ./objs
SRCDIR = ./srcs
INCLUDE = includes
LIBFT = ./libft/libft.a

SRCS = main.c

OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

CFLAGS = -Wall -Wextra -Werror
IFLAGS = -Iincludes -Ilibft/includes
LFLAGS = -Llibft
LIBFLAGS = -lft -lreadline

VPATH = $(SRCDIR)

#VPATH = $(SRCDIR):$(SRCDIR)/ft_cdlst:$(SRCDIR)/ps_wrap:$(SRCDIR)/stacks:$(SRCDIR)/ps_utils:$(SRCDIR)/sort

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(NAME): $(LIBFT) $(OBJS)
	$(GCC) $(CFLAGS) $(IFLAGS) $(OBJS) -o $@ $(LFLAGS) $(LIBFLAGS)

$(OBJDIR)/%.o: %.c
	mkdir -p $(OBJDIR)
	$(GCC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(LIBFT):
	make --directory ./libft/

libft_clean:
	make --directory ./libft/ clean

$(OBJDIR)/%.o: %.c
	mkdir -p $(OBJDIR)
	$(GCC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean: libft_clean
	rm -f $(OBJS)
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME) ./libft/libft.a

re: fclean all

norminette:
	norminette ./srcs

.PHONY: all clean fclean re bonus libft norminette
