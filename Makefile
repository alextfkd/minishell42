NAME = minishell
CC = cc -g
GCC = gcc -g

OBJDIR = ./objs
SRCDIR = ./srcs
LIBFT = ./libft/libft.a

SRCS = main.c 

OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

CFLAGS = -Wall -Wextra -Werror
IFLAGS = -Iincludes -Ilibft
LFLAGS = -Llibft
LIBFLAGS = -lft 

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

.PHONY: all clean fclean re bonus libft
