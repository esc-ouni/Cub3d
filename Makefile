# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: idouni <idouni@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/24 18:36:33 by idouni            #+#    #+#              #
#    Updated: 2023/08/05 17:04:09 by idouni           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME   = cub3D
MATH   = -O3 -ffast-math
MLX    = -lmlx -framework OpenGL -framework AppKit
CC     = cc
RM     = rm -rf
FLAGS  = -Wall -Wextra -Werror
HR     = src/cub.h
LHR    = libft/libft.h
GHR    = g_n_l/get_next_line.h
TLS    = src/cub.c \
		src/tools_0.c \
		src/tools_1.c \
		src/tools_2.c \
		src/tools_3.c \
		src/tools_4.c \
		src/tools_5.c \
		src/tools_6.c \
		src/tools_7.c \
		src/tools_8.c \
		src/tools_9.c \
		src/tools_10.c \
		src/tools_11.c \
		src/tools_12.c \
		src/tools_13.c \
		src/tools_14.c \
		src/tools_15.c \
		src/tools_16.c \
		src/tools_17.c \
		src/tools_18.c \
		src/tools_19.c \
		src/tools_20.c \
		src/tools_21.c \
		g_n_l/get_next_line.c \
		g_n_l/get_next_line_utils.c \

LBFT   = libft/libft.a

OBJ_T  = $(TLS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ_T) $(HR) $(GHR) $(LHR)
	@make -C libft
	@$(CC) $(FLAGS) $(MATH) $(MLX) $(LBFT) $(OBJ_T) -o $(NAME) -lm
	@clear && echo "==$(NAME)_compiled==========="


%.o: %.c $(HR) $(GHR) $(LHR)
	$(CC) $(FLAGS) $(MATH) -c $< -o $@ 

clean:
	@make clean -C libft
	$(RM) $(OBJ_M)
	$(RM) $(OBJ_T)
	@clear && echo "==Object_files_deleted======="

fclean: clean
	@make fclean -C libft
	$(RM) $(NAME)
	$(RM) .vscode
	$(RM) *.dSYM
	@clear && echo "==All_created_files_deleted=="

re: fclean all
	@clear && echo "==Compilation_reseted========"

.PHONY: all clean fclean re