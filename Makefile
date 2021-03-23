# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkrinova <lkrinova@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/12 13:23:54 by lkrinova          #+#    #+#              #
#    Updated: 2021/03/13 20:26:51 by lkrinova         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D

HEADER  = cub3d.h
CC		= gcc

CFLAGS	= -Wall -Wextra -Werror -g

SRC		= cub3d.c\
		mlx.c\
		render.c\
		ray_config.c\
		parsing/parser.c\
		parsing/textures_rgb.c\
		parsing/map_config.c\

OBJ		= $(SRC:.c=.o)

all:	$(NAME)

LIB = $(LIB_DIR)libft.a

LIB_DIR = libft/

$(LIB): FORCE
	$(MAKE) -C $(LIB_DIR)

$(NAME): $(LIB) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ -lft -L$(LIB_DIR) \
		-lmlx -framework OpenGL -framework AppKit

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR) -I$(LIB_DIR)

clean:
	$(RM) $(OBJ)
	$(MAKE) -C $(LIB_DIR) $@

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIB)

re:		fclean all

FORCE:
