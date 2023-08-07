#include "cub.h"

// void 	leak()
// {
// 	system("leaks a.out");
// }

int main(int argc, char const *argv[])
{
	void	*mlx;
	// void	*xpm;
	// int		width;
	// int		height;

	// atexit(leak);
	// mlx = mlx_init();
	// xpm = mlx_xpm_file_to_image(mlx, "", &width, &height);
	// if (!xpm)
	// 	write(1, "\n\nholllla\n", 11);
	// free(mlx);
	printf("%p\n", mlx);
	mlx = malloc(50);
	printf("%p\n", mlx);
	return 0;
}
