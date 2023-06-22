FLAGS = -Wall -Wextra -Werror #-fsanitize=address
MATH = -Oz -ffast-math
MLX = -lmlx -framework OpenGL -framework AppKit

all:
	gcc $(FLAGS) $(MATH) $(MLX)  Get_next_line/*.c ./*.c -o Cub -lm
	./Cub
	clear

fclean:
	rm -rf *.o
	rm -rf Cub
	clear

re: fclean all 