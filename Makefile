# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: idouni <idouni@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/24 18:36:33 by idouni            #+#    #+#              #
#    Updated: 2023/07/28 00:30:04 by idouni           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(WSL_DISTRO_NAME), Ubuntu)
FLAGS = -Wall -Wextra -Werror
MATH = -O3 -ffast-math
MLX = -lmlx -framework OpenGL -framework AppKit

LIBF_DIR := LIBFT
GNL_DIR := G_N_L
SRC_DIR := Src

LIBF_SRCS := $(wildcard $(LIBF_DIR)/*.c)
GNL_SRCS := $(wildcard $(GNL_DIR)/*.c)
SRC_SRCS := $(wildcard $(SRC_DIR)/*.c)

all:
	clear
	# gcc $(FLAGS) $(MATH) $(MLX)  LIBF/*.c G_N_L/*.c ./Src/*.c -o Cub -lm
	cc $(LIBF_SRCS) $(GNL_SRCS) $(SRC_SRCS) -L minilibx-linux/libmlx_Linux.a -L minilibx-linux/libmlx.a -lmlx -lXext -lX11 -o Cub -lm
	valgrind --leak-check=full ./Cub Ext/map.cub


clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET)

fclean:
	rm -rf *.o *.dSYM .vscode
	rm -rf Cub
	clear

re: fclean all 
else
NAME = Cub3D
FLAGS = -Wall -Wextra -Werror #-fsanitize=undefined,address -g
MATH = -O3 -ffast-math
MLX = -lmlx -framework OpenGL -framework AppKit

all:
	clear
	gcc $(FLAGS) $(MATH) $(MLX)  LIBF/*.c Get_next_line/*.c ./Src/*.c -o $(NAME) -lm
	# clang LIBF/*.c Get_next_line/*.c ./Src/*.c -L minilibx-linux/libmlx_Linux.a -lmlx -lXext -lX11 -o Cub -lm -lbsd
	./$(NAME) Ext/map.cub

fclean:
	rm -rf *.o *.dSYM .vscode
	rm -rf $(NAME)
	clear

re: fclean all 

endif
