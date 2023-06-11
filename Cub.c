#include "Cub.h"

void parse_file(int argc, char const *argv[])
{
	if ()
	exit(EXIT_FAILURE);
}


int main(int argc, char const *argv[])
{
	t_collector *collector;
	t_img_collector *img_collector;
	t_vars 		*vars;
	
	collector = NULL;
	img_collector = NULL;

    parse_file(argc, argv);
	vars = NULL;
	vars = h_malloc(&collector, sizeof(t_vars), vars);
	vars->img_collector = &img_collector;
	vars->collector = &collector;
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "Cub");
	if(!vars->mlx || !vars->win)
	{
		write (2, "\033[0;32mMLX_FAILED\033[0;37m\n", 29);
		ft_destroy_all_images(vars);
		ft_collectorclear(vars->collector);
		exit (1);
	}
	draw_in_image(vars, 1);
	// draw_2d_map(vars);
	mlx_hook(vars->win, 17, 0, ft_ext, vars);
	mlx_key_hook(vars->win, handler, vars);
	mlx_loop(vars->mlx);
	return 0;
}
