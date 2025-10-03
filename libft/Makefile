NAME	= libft.a
SRCDIR	= .
OBJDIR	= .
BONUSDIR	= .
SRCS	+= $(SRCDIR)/ft_atoi.c
SRCS	+= $(SRCDIR)/ft_bzero.c
SRCS	+= $(SRCDIR)/ft_calloc.c
SRCS	+= $(SRCDIR)/ft_isalnum.c
SRCS	+= $(SRCDIR)/ft_isalpha.c
SRCS	+= $(SRCDIR)/ft_isascii.c
SRCS	+= $(SRCDIR)/ft_isdigit.c
SRCS	+= $(SRCDIR)/ft_isprint.c
SRCS	+= $(SRCDIR)/ft_isprint.c
SRCS	+= $(SRCDIR)/ft_itoa.c
SRCS	+= $(SRCDIR)/ft_memchr.c
SRCS	+= $(SRCDIR)/ft_memcmp.c
SRCS	+= $(SRCDIR)/ft_memcpy.c
SRCS	+= $(SRCDIR)/ft_memmove.c
SRCS	+= $(SRCDIR)/ft_memset.c
SRCS	+= $(SRCDIR)/ft_putchar_fd.c
SRCS	+= $(SRCDIR)/ft_putendl_fd.c
SRCS	+= $(SRCDIR)/ft_putnbr_fd.c
SRCS	+= $(SRCDIR)/ft_putstr_fd.c
SRCS	+= $(SRCDIR)/ft_split.c
SRCS	+= $(SRCDIR)/ft_strdup.c
SRCS	+= $(SRCDIR)/ft_strlen.c
SRCS	+= $(SRCDIR)/ft_strlcpy.c
SRCS	+= $(SRCDIR)/ft_strlcat.c
SRCS	+= $(SRCDIR)/ft_strchr.c
SRCS	+= $(SRCDIR)/ft_strrchr.c
SRCS	+= $(SRCDIR)/ft_striteri.c
SRCS	+= $(SRCDIR)/ft_strjoin.c
SRCS	+= $(SRCDIR)/ft_strncmp.c
SRCS	+= $(SRCDIR)/ft_strmapi.c
SRCS	+= $(SRCDIR)/ft_strnstr.c
SRCS	+= $(SRCDIR)/ft_strtrim.c
SRCS	+= $(SRCDIR)/ft_substr.c
SRCS	+= $(SRCDIR)/ft_tolower.c
SRCS	+= $(SRCDIR)/ft_toupper.c
BONUS	+= $(BONUSDIR)/ft_lstnew.c
BONUS	+= $(BONUSDIR)/ft_lstadd_front.c
BONUS	+= $(BONUSDIR)/ft_lstsize.c
BONUS	+= $(BONUSDIR)/ft_lstlast.c
BONUS	+= $(BONUSDIR)/ft_lstadd_back.c
BONUS	+= $(BONUSDIR)/ft_lstdelone.c
BONUS	+= $(BONUSDIR)/ft_lstclear.c
BONUS	+= $(BONUSDIR)/ft_lstiter.c
BONUS	+= $(BONUSDIR)/ft_lstmap.c
OBJS	= $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
BOBJS	= $(BONUS:$(BONUSDIR)/%.c=$(BONUSDIR)/%.o)

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -Iincludes
AR		= ar
ARFLAGS	= rcs

all: $(NAME)

$(NAME):	$(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(OBJS) $(BOBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS) $(BOBJS)

$(BONUSDIR)/%.o: $(BONUSDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BOBJS)

fclean: clean
	rm -f $(NAME)

re:	fclean all bonus

.PHONY: all clean fclean re bonus
