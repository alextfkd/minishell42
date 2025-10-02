# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/31 20:34:58 by htsutsum          #+#    #+#              #
#    Updated: 2025/08/22 11:31:18 by htsutsum         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
CC = cc
INCDIR = include
LIBFTDIR = libft
MLXDIR = minilibx-linux
INCLUDES = $(INCDIR) $(LIBFTDIR)/include $(MLXDIR)
CFLAGS = -Wall -Wextra -Werror -O2 -march=native $(addprefix -I,$(INCLUDES))
MLXFLAGS = -L$(MLXDIR) -lmlx -lXext -lX11 -lm
SRCDIR = src
OBJDIR = obj

FILES_FRACTOL = main_bonus.c\
				parse_args_bonus.c\
				display.c\
				render_bonus.c \
				fractal_bonus.c\
				key_mouse_event_bonus.c\
				expose_resize_event.c\
				color_bonus.c\
				complex.c

HEADER = $(INCDIR)/fractal_bonus.h\
         $(INCDIR)/color_bonus.h\
		 $(INCDIR)/complex.h

SRC = $(addprefix $(SRCDIR)/, $(FILES_FRACTOL))
OBJ = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))

LIBFT = $(LIBFTDIR)/libft.a
MLX = $(MLXDIR)/libmlx.a
MLX_REPO = https://github.com/42Paris/minilibx-linux.git

all: $(NAME)

$(LIBFT): $(LIBFTDIR)
	@make -C $(LIBFTDIR)

$(MLX): | $(MLXDIR)
	$(MAKE) -C $(MLXDIR)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLXFLAGS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADER)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clone:
	@if [ ! -d "$(MLXDIR)" ]; then \
		echo "Cloning MinilibX from $(MLX_REPO)"; \
		git clone $(MLX_REPO) ; \
	else \
		echo "$(MLXDIR) directory already exists, skipping clone."; \
	fi

bonus: all

clean:
	@make -C $(LIBFTDIR) clean
	@make -C $(MLXDIR) clean
	@rm -rf $(OBJDIR)

fclean: clean
	@make -C $(LIBFTDIR) fclean
	@make -C $(MLXDIR) clean
	@rm -rf $(NAME)

re: fclean all

test: $(NAME)
	valgrind -s --track-fds=yes --trace-children=yes --leak-check=full --track-origins=yes --show-leak-kinds=all ./fractol m

.PHONY: all bonus clone clean fclean re test