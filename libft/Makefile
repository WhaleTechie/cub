# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkrinova <lkrinova@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/12 13:23:54 by lkrinova          #+#    #+#              #
#    Updated: 2021/03/03 14:22:13 by lkrinova         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

HEADER  = libft.h
CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

SRC		= ft_atoi.c \
        ft_isalnum.c\
        ft_isalpha.c\
        ft_isascii.c\
        ft_isdigit.c\
        ft_isprint.c\
        ft_strlen.c\
        ft_strlcpy.c\
        ft_strlcat.c\
        ft_strncmp.c\
        ft_strchr.c\
        ft_strrchr.c\
        ft_strnstr.c\
        ft_tolower.c\
        ft_toupper.c\
        ft_memset.c\
        ft_memcpy.c\
        ft_memccpy.c\
        ft_bzero.c\
        ft_memmove.c\
        ft_memchr.c\
        ft_memcmp.c\
        ft_calloc.c\
        ft_strdup.c\
        ft_putchar_fd.c\
        ft_putstr_fd.c\
        ft_putendl_fd.c\
        ft_substr.c\
        ft_strjoin.c\
        ft_strnew.c\
        ft_strtrim.c\
        ft_split.c\
        ft_strmapi.c\
        ft_itoa.c\
        ft_putnbr_fd.c\
        get_next_line.c\


OBJ		= $(SRC:.c=.o)

all:	$(NAME)

%.o : %.c $(HEADER)
		$(CC) $(CFLAGS)	-c	$<
		ar rc $(NAME)	$@
$(NAME):$(OBJ) Makefile

clean:
		rm -f $(OBJ)

fclean:	clean
			rm -f $(NAME)

re:		fclean all

.PHONY: all clean fclean re
