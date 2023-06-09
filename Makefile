all:
	gcc -Wall -Wextra -Werror -Oz -ffast-math -lmlx -framework OpenGL -framework AppKit *.c -o Cub
	clear
	./Cub

fclean:
	rm -rf *.o
	rm -rf Cub

re: fclean all 