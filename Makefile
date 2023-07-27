# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: idouni <idouni@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/24 18:36:33 by idouni            #+#    #+#              #
#    Updated: 2023/07/27 20:51:15 by idouni           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME   = cub3D
MATH   = -O3 -ffast-math
MLX    = -lmlx -framework OpenGL -framework AppKit
CC     = cc
RM     = rm -rf
FLAGS  = -Wall -Wextra -Werror #-fsanitize=address -g
HR     = Src/cub.h
LHR    = LIBFT/libft.h
GHR    = G_N_L/get_next_line.h
TLS    = Src/cub.c \
		Src/memory.c \
		Src/tools_0.c \
		Src/tools_1.c \
		Src/tools_10.c \
		Src/tools_11.c \
		Src/tools_12.c \
		Src/tools_13.c \
		Src/tools_14.c \
		Src/tools_15.c \
		Src/tools_16.c \
		Src/tools_17.c \
		Src/tools_18.c \
		Src/tools_2.c \
		Src/tools_3.c \
		Src/tools_4.c \
		Src/tools_5.c \
		Src/tools_6.c \
		Src/tools_7.c \
		Src/tools_8.c \
		Src/tools_9.c \
		G_N_L/get_next_line.c \
		G_N_L/get_next_line_utils.c \

LBFT   = LIBFT/libft.a

OBJ_T  = $(TLS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ_T) $(HR) $(GHR) $(LHR)
	@make -C LIBFT
	@$(CC) $(FLAGS) $(MATH) $(MLX) $(LBFT) $(OBJ_T) -o $(NAME) -lm
	@clear && echo "==$(NAME)_compiled==========="


%.o: %.c $(HR) $(GHR) $(LHR)
	$(CC) $(FLAGS) $(MATH) -c $< -o $@ 

clean:
	@make clean -C LIBFT
	$(RM) $(OBJ_M)
	$(RM) $(OBJ_T)
	@clear && echo "==Object_files_deleted======="

fclean: clean
	@make fclean -C LIBFT
	$(RM) $(NAME)
	$(RM) .vscode
	$(RM) *.dSYM
	@clear && echo "==All_created_files_deleted=="

re: fclean all
	@clear && echo "==Compilation_reseted========"

.PHONY: all clean fclean re