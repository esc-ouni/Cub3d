#include "Cub.h"

void 	draw_player(t_vars *vars, int px, int py)
{
	int i, j;
	t_data 		*p_img;
	t_vector 	origin;
	t_vector 	direction;
	

	origin.x = (WIDTH/2) + px;
	origin.y = (HEIGHT/2) + py;
	direction.x = (WIDTH/2) + px;
	direction.y = (HEIGHT/2) + py;
	// ray = NULL;
	// ray = h_malloc(vars->collector, sizeof(t_ray), ray);
	// ray->origin->x = (WIDTH/2) + px;
	// ray->origin->y = (HEIGHT/2) + py;
	// ray->direction->x = (WIDTH/2) + 100;
	// ray->direction->y = (HEIGHT/2) + 100;

	p_img = draw_2d_map(vars);
	int x = (WIDTH/2 - 5) + px;
	int y = (HEIGHT/2 - 5)+ py;
	
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
	// x = (WIDTH/2 - 5) + px;
	// y = (HEIGHT/2) + py;
	// while (i < 30)
	// {
	// 	my_mlx_pixel_put(p_img, x + i, y, BLUE);
	// 	i++;
	// }
	// draw_ray(vars, p_img, ray);
	draw_ray(vars->mlx, vars->win, origin, direction, 50, BLUE);
	// mlx_clear_window(vars->mlx, vars->win);
	// mlx_put_image_to_window(vars->mlx, vars->win,p_img->img_ptr, 0, 0);
}