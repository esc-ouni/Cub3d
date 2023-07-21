ifeq ($(WSL_DISTRO_NAME), Ubuntu)
FLAGS = -Wall -Wextra -Werror 
MATH = -Oz -ffast-math
MLX = -lmlx -framework OpenGL -framework AppKit

LIBF_DIR := LIBF
GNL_DIR := Get_next_line
SRC_DIR := Src

LIBF_SRCS := $(wildcard $(LIBF_DIR)/*.c)
GNL_SRCS := $(wildcard $(GNL_DIR)/*.c)
SRC_SRCS := $(wildcard $(SRC_DIR)/*.c)

all:
	clear
	# gcc $(FLAGS) $(MATH) $(MLX)  LIBF/*.c Get_next_line/*.c ./Src/*.c -o Cub -lm
	cc $(LIBF_SRCS) $(GNL_SRCS) $(SRC_SRCS) -L minilibx-linux/libmlx_Linux.a -lmlx -lXext -lX11 -o Cub -lm
	#./Cub Ext/map.cub


clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET)

fclean:
	rm -rf *.o *.dSYM .vscode
	rm -rf Cub
	clear

re: fclean all 
else
NAME = Cub3D
FLAGS = -Wall -Wextra -Werror 
MATH = -Oz -ffast-math
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
