# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdeyirme <rdeyirme@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/04 22:09:40 by ekarali           #+#    #+#              #
#    Updated: 2023/06/10 15:59:29 by rdeyirme         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g
MLXFLAGS	= -framework OpenGL -framework AppKit
SRCS 		= gnl/get_next_line.c main.c checker.c reader.c data.c utils.c end.c game.c move.c init.c texture.c
HEADER 		= cub3d.h
OBJS 		= $(SRCS:.c=.o)
LIB_MLX		= ./mlx/libmlx.a
OTHERS 		= ./libft/libft.a ./printf/libftprintf.a
RM			= rm -rf


all: $(NAME) 

$(NAME):$(LIB_MLX) $(OTHERS) $(OBJS)
	$(CC) $(OBJS) $(MLXFLAGS) -o $(NAME) $(OTHERS) $(LIB_MLX) $(CFLAGS) 

%.o: %.c 
	$(CC) $(CFLAGS) -c $^ -o $@

$(LIB_MLX) :
	curl https://cdn.intra.42.fr/document/document/14741/minilibx_opengl.tgz -o mlx.tgz
	tar -xf mlx.tgz
	$(RM) mlx.tgz
	mv ./minilibx_opengl_20191021 ./mlx
	make -C ./mlx

$(OTHERS):
	make -C ./libft
	make -C ./printf

clean : cleanothers
	$(RM) $(OBJS)
	$(RM) mlx/

cleanothers :
	make clean -C ./libft
	make clean -C ./printf

fclean : clean
	$(RM) $(NAME)
	make fclean -C ./libft
	make fclean -C ./printf

re : fclean all

.PHONY : all fclean clean re
