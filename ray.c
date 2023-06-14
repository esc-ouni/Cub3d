#include "Cub.h"

void draw_ray(t_data *p_img, t_vars *vars, t_vector origin, t_vector direction, int length)
{
	// int k = -25;


	int x1;
	int y1;
	int x2;
	int y2;

	float dx;
	float dy;
	float steps;
	float x_inc;
	float y_inc;

	float x;
	float y;

	// while(k < 25)
	// {
		x1 = (int)origin.x;
		y1 = (int)origin.y;
		x2 = (int)(origin.x + (direction.x)* length);
		y2 = (int)(origin.y + (direction.y)* length);

		dx = x2 - x1;
		dy = y2 - y1;
		steps = fmax(fabs(dx), fabs(dy));
		x_inc = dx / steps;
		y_inc = dy / steps;

		x = x1;
		y = y1;
		for (int i = 0; i < 500; i++)
		{
			// mlx_pixel_put(vars->mlx, vars->win, (int)x, (int)y, BLUE);
			my_mlx_pixel_put(p_img, (int)x, (int)y,BLUE);
			if (vars->map[((((int)fabs(y)+(int)y_inc))/50)][(((int)fabs(x) + (int)x_inc)/50)] == '0')
			{
				x += x_inc;
				y += y_inc;
			}
			else
				return ;
		}
	// 	k++;

	// }
}
