CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
INCDIR = include
OBJDIR = obj
SRCDIR = src
INCLUDES = -I$(INCDIR)
HEADER = $(INCDIR)/libft.h
LIBFT_FILES = ft_strlen.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strnstr.c \
		ft_strcmp.c \
		ft_strncmp.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memchr.c \
		ft_memmove.c \
		ft_memcmp.c \
		ft_atod.c \
		ft_atoi.c \
		ft_isalpha.c \
		ft_isspace.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c\
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_free_tab.c
B_FILES = ft_lstnew_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstsize_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstadd_back_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstmap_bonus.c

LIBFT_SRC = $(addprefix $(SRCDIR)/,$(LIBFT_FILES))
B_SRC = $(addprefix $(SRCDIR)/,$(B_FILES))

SRC = $(LIBFT_SRC) $(B_SRC) $(GNL_SRC) $(FT_PRINTF_FILES)

LIBFT_OBJ=$(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(LIBFT_SRC))
B_OBJ=$(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(B_SRC))
OBJ = $(LIBFT_OBJ) $(B_OBJ)

# $(info DEBUG: LIBFT_SRC = $(LIBFT_SRC))
# $(info DEBUG: B_SRC = $(B_SRC))
# $(info DEBUG: LIBFT_OBJ = $(LIBFT_OBJ))
# $(info DEBUG: B_OBJ = $(B_OBJ))
# $(info DEBUG: GML_SRC = $(GNL_SRC))
# $(info DEBUG: GNL_OBJ = $(B_OBJ))
# $(info DEBUG: FT_PRINTF_SRC = $(FT_PRINTF_SRC))
# $(info DEBUG: FT_PRINTF_OBJ = $(FT_PRINTF_OBJ))
# $(info DEBUG: OBJ = $(OBJ))

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

$(OBJDIR)/%.o:$(SRCDIR)/%.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:all clean fclean re
