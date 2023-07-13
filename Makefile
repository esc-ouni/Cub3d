FLAGS = -Wall -Wextra -Werror #-fsanitize=undefined,address -g
MATH = -Oz -ffast-math
MLX = -lmlx -framework OpenGL -framework AppKit

all:
	clear
	# gcc $(FLAGS) $(MATH) $(MLX)  LIBF/*.c Get_next_line/*.c ./Src/*.c -o Cub -lm
	clang LIBF/*.c Get_next_line/*.c ./Src/*.c -L minilibx-linux/libmlx_Linux.a -lmlx -lXext -lX11 -o Cub -lm -lbsd
	#./Cub Ext/map.cub

fclean:
	rm -rf *.o *.dSYM .vscode
	rm -rf Cub
	clear

re: fclean all 