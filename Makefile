FLAGS = #-Wall -Wextra -Werror #-fsanitize=undefined,address -g
MATH = -Oz -ffast-math
MLX = -lmlx -framework OpenGL -framework AppKit

all:
	clear
	gcc $(FLAGS) $(MATH) $(MLX)  Get_next_line/*.c ./Src/*.c -o Cub -lm
	./Cub

fclean:
	rm -rf *.o *.dSYM .vscode
	rm -rf Cub
	clear

re: fclean all 