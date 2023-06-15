#include "Cub.h"

void draw_ray(t_data *p_img, t_vars *vars, t_vector origin, t_vector direction, int length)
{
	if ((direction.y == origin.y) && (direction.x == origin.x))
		return;
	float i = 0;
	float steps;
	float x_inc;
	float y_inc;
	float x = origin.x;
	float y = origin.y;
	float dy = (direction.y - origin.y);
	float dx = (direction.x - origin.x);


	if (fabs(dx) >= fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);

	x_inc = dx / steps;
	y_inc = dy / steps;

	while (i < 200)
	{
		my_mlx_pixel_put(p_img, (int)x, (int)y, BLUE);
		x += x_inc;
		y += y_inc;
		i ++;
	}
}
