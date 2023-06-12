#include "Cub.h"

void 	draw_player(t_vars *vars, int px, int py)
{
	int i, j;
	t_data 		*p_img;
	
	p_img = draw_2d_map(vars)
;
	int x = 895 + px;
	int y = 345 + py;
	
	i = 0;
	j = 0; 
	while(i < 10)
	{
		while(j < 10)
		{
			my_mlx_pixel_put(p_img, x + i, y + j, BLUE);
			j++;
		}
		i++;
		j = 0;
	}
	mlx_clear_window(vars->mlx, vars->win);
	mlx_put_image_to_window(vars->mlx, vars->win,p_img->img_ptr, 0, 0);
}