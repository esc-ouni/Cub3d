#include "Cub.h"

void 	draw_player(t_vars *vars, int px, int py, t_vector *direction, float angle)
{
	int i, j, k;
	t_data 		*p_img;
	t_vector 	origin;
	t_vector 	direct;
	float       angle -= 0.75;
	
	direct = *direction;
	origin.x = (WIDTH/2) + px;
	origin.y = (HEIGHT/2) + py;

	p_img = draw_2d_map(vars);
	int x = (WIDTH/2) + px;
	int y = (HEIGHT/2) + py;
	
	i = -5;
	j = -5; 
	k = 0; 
	while(i < 5)
	{
		while(j < 5)
		{
			my_mlx_pixel_put(p_img, x + i, y + j, BLUE);
			j++;
		}
		i++;
		j = -5;
	}
	mlx_clear_window(vars->mlx, vars->win);
	while (k<500)
	{
		rotate_vector(&direct, angle+=0.0003);
		draw_ray(p_img, vars, origin, direct, 400);
		k++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win,p_img->img_ptr, 0, 0);
	// ft_destroy_all_images(vars);
	// ft_collectorclear(vars->collector, TMP);
}