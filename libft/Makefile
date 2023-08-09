# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: idouni <idouni@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/12 14:32:47 by idouni            #+#    #+#              #
#    Updated: 2023/07/24 18:55:07 by idouni           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME   = libft.a
CC     = cc
RM     = rm -rf
FLAGS  = -Wall -Wextra -Werror -fsanitize=address -g
AR     = ar -rc
HR     = libft.h
PR     = ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_strchr.c \
		ft_strcmp.c \
		ft_striteri.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_tolower.c \
		ft_toupper.c \

OBJ  	= $(PR:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ) $(HR)
	$(AR) $(NAME) $(OBJ)

%.o: %.c $(HR)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(B_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all bonus clean fclean re