# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esamad-j <esamad-j@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/15 08:41:10 by aoteo-be          #+#    #+#              #
#    Updated: 2023/11/30 03:02:31 by esamad-j         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and compilation flags
CC          = gcc
CFLAGS	    = -g -Wall -Wextra -Werror

# Directories
INC_DIR		= ./includes

# Executable
NAME		= cub3D

# Sources
SRCS = check_wall.c cub3D.c map_errors.c map_read.c ray.c

# Libft
LIBFT		= ./libft/libft.a
LDLFLAG 	= -L libft/ -lft

#Object files
OBJS        = $(SRCS:.c=.o)

all :       $(NAME)

$(NAME):    $(OBJS)
			make -C libft
			$(CC) $(CFLAGS) $(LDLFLAG) $(OBJS) -IINC_DIR -lmlx -framework OpenGL -framework AppKit -o $(NAME)
#			$(CC) $(CFLAGS) $(LDLFLAG) $(OBJS) -IINC_DIR -lmlx -L mlx/ -framework OpenGL -framework AppKit -o $(NAME)

clean :
		    @rm -fv $(OBJS)
			@rm -fv $(OBJS_BONUS)

fclean :    clean
		    @rm -fv $(NAME)
			@rm -fv $(BNAME)

re :        fclean all

.PHONY :    all bonus clean fclean make re