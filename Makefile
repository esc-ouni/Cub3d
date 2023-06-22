FLAGS = -Wall -Wextra -Werror #-fsanitize=undefined,address -g
MATH = -O3 -ffast-math
MLX = -lmlx -framework OpenGL -framework AppKit

all:
	gcc $(FLAGS) $(MATH) $(MLX)  Get_next_line/*.c ./*.c -o Cub -lm
	clear
	./Cub

fclean:
	rm -rf *.o *.dSYM .vscode
	rm -rf Cub
	clear

re: fclean all 