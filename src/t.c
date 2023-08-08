# include "mlx.h"
# include <unistd.h>
# include <stdlib.h>

void 	leak()
{
	system("leaks a.out");
}

int main(int argc, char const *argv[])
{
	void	*mlx;
	void	*xpm;
	int		width;
	int		height;

	atexit(leak);
	mlx = mlx_init();
	xpm = mlx_xpm_file_to_image(mlx, "/Users/idouni/Desktop/Cub3d/ext/no.xpm'", &width, &height);
	if (!xpm)
		write(1, "\n\nholllla\n", 11);
	free(xpm);
	free(mlx);
	system("leaks a.out");
	exit (0);
}
