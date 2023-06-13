#include "Cub.h"

void draw_ray(t_vars *vars, t_vector origin, t_vector direction, int length)
{
	int k = 0;

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

	// while(k < 70)
	// {
		x1 = (int)origin.x;
		y1 = (int)origin.y;
		x2 = (int)(origin.x + (direction.x += 50)* length);
		y2 = (int)(origin.y + (direction.y += 50)* length);

		dx = x2 - x1;
		dy = y2 - y1;
		steps = fmax(fabs(dx), fabs(dy));
		x_inc = dx / steps;
		y_inc = dy / steps;

		x = x1;
		y = y1;
		for (int i = 0; i < length; i++)
		{
			// printf("x : %d, y : %d\n",((int)origin.x + (int)x), ((int)origin.y + (int)y));
			mlx_pixel_put(vars->mlx, vars->win, (int)x, (int)y, BLUE);
			// if (vars->map[(((int)origin.x + (int)x)/50)][(((int)origin.y + (int)y)/50)] == '0')
			// {
			x += x_inc;
			y += y_inc;
			// }
			// else
			// 	return ;
		}
// 		k++;

// 	}
}
