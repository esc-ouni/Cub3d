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
	xpm = mlx_xpm_file_to_image(mlx, "/Use.xpm", &width, &height);
	free(mlx);
	free(xpm);
	// system("leaks a.out");
	return (0);
}
