#include <libc.h>
#include <mlx.h>

int main(int argc, char const *argv[])
{
	(void)argc;
	(void)argv;
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 1080, 720, "Cub");
	mlx_loop(mlx);
	return 0;
}
