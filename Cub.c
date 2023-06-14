#include "Cub.h"

int main(int argc, char const *argv[])
{
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
    vars->map = parse_file(&collector, argc, argv);
	if(!vars->mlx || !vars->win)
	{
		write (2, "\033[0;32mMLX_FAILED\033[0;37m\n", 29);
		ft_destroy_all_images(vars);
		ft_collectorclear(vars->collector);
		exit (1);
	}
	vars->pos = NULL;
	vars->pos = h_malloc(vars->collector, sizeof(t_vectorr), vars->pos);
	vars->pos->x = 0;
	vars->pos->y = 0;
	vars->direction = NULL;
	vars->direction = h_malloc(vars->collector, sizeof(t_vector), vars->direction);
	vars->direction->x = 900;
	vars->direction->y = 350;
	mlx_hook(vars->win, 17, 0, ft_ext, vars);
	mlx_hook(vars->win, 2, 1L << 0, handler, vars);
	mlx_hook(vars->win, 6, 0, mouse_movement, vars);
	mlx_loop(vars->mlx);
	return 0;
}
