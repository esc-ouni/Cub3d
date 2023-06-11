#include "Cub.h"

void	draw_2d_map(t_vars *vars)
{
	t_data	*map;
	map = new_image(vars);
	mlx_clear_window(vars->mlx, vars->win);
	
	//draw


	mlx_put_image_to_window(vars->mlx, vars->win, map->img_ptr, 0, 0);
}
