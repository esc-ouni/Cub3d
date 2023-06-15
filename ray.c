#include "Cub.h"

void draw_ray(t_data *p_img, t_vars *vars, t_vector origin, t_vector direction, int length)
{
	if ((direction.y == origin.y) && (direction.x == origin.x))
		return ;
	int i = 0;
	float steps;
	float x_inc;
	float y_inc;
	float x = origin.x;
	float y = origin.y;
	float dy = (direction.y - origin.y);
	float dx = (direction.x - origin.x);

	if(fabs(dx) >= fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);

	printf("origin    x : %f, y = %f\n", origin.x, origin.y);
	printf("direction x : %f, y = %f\n\n", direction.x, direction.y);
	x_inc = dx / steps;
	y_inc = dy / steps;

	while (i < steps)
	{
		my_mlx_pixel_put(p_img, (int)x, (int)y,BLUE);
		x += x_inc;
		y += y_inc;
		i++;
	}
}
