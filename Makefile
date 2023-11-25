# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esamad-j <esamad-j@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/14 00:00:24 by esamad-j          #+#    #+#              #
#    Updated: 2023/11/20 22:34:22 by esamad-j         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

CFLAGS		= -Wall -Werror -Wextra

CC			= gcc

LIBFT		= ./libft/libft.a

SRCS		= cub3D.c map_errors.c map_read.c check_wall.c

OBJS		= $(SRCS:%.c=%.o)

LDLFLAG 	= -L libft/ -lft

all: $(NAME)

$(NAME):	$(OBJS)
			make -C libft
			$(CC) $(CFLAGS) $(LDLFLAG) $(OBJS) -o $(NAME)

clean:
			make -C libft clean
			rm -f $(OBJS)

fclean: 	clean
			rm -f $(NAME)

re: 		fclean all

.PHONY: all clean fclean re bonus