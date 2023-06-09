#include "Cub.h"

int main(int argc, char const *argv[])
{
	(void)argc;
	(void)argv;
	t_collector *collector;
	t_img_collector *img_collector;
	t_vars 		*vars;
	
	collector = NULL;
	img_collector = NULL;

	vars = NULL;
	vars = h_malloc(&collector, sizeof(t_vars), vars);
	vars->img_collector = &img_collector;
	vars->collector = &collector;
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "Cub");

	mlx_hook(vars->win, 17, 0, ft_ext, vars);
	mlx_key_hook(vars->win, handler, vars);
	mlx_loop(vars->mlx);
	return 0;
}
