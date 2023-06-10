FLAGS = #-Wall -Wextra -Werror
MATH = -Oz -ffast-math
MLX = -lmlx -framework OpenGL -framework AppKit

all:
	gcc $(FLAGS) $(MATH) $(MLX) *.c -o Cub
	clear
	./Cub

fclean:
	rm -rf *.o
	rm -rf Cub

re: fclean all 