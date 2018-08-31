# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgleason <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/05 19:47:07 by cgleason          #+#    #+#              #
#    Updated: 2018/08/29 12:23:55 by cgleason         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = @gcc

CFLAGS = -Wall -Wextra -Werror

LIBFT = -L./libft -lft

MINILIBX = -L./minilibx_macos -lmlx -framework OpenGL -framework AppKit

SRC = main.c interpolators.c press_and_click.c colors.c helpers.c hooks.c \
		draw_squad.c

OBJS = $(SRC:.c=.o)

$(NAME): libft/libft.a $(OBJS) fdf.h
	$(CC) $(CFLAGS) $(LIBFT) $(MINILIBX) $(OBJS) -o $(NAME)

libft/libft.a:
	@cd libft && make

.PHONY: clean fclean all re

clean:
	@rm -f $(OBJS)
	@cd libft && make clean

fclean: clean
	@rm -f $(NAME)
	@cd libft && make fclean

all: $(NAME)

re: fclean all
