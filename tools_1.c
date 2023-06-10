#include "Cub.h"

void	draw_in_image(t_vars *vars, int r)
{
	int t = 0;
	int i = 0;
	int k = 0;
	int x = 0;
	int p = 0;
	int y = 0;
	int l = 0x60BADD;
	int lr = 598642;
	t_data		*img;

	img = new_image(vars);
	if(r)
	{
		l = 598642;
		lr = 0x60BADD;
	}
	while(x < WIDTH)
	{
		while(y < HEIGHT)
		{
			while (i)
			{
				my_mlx_pixel_put(img, x, p, lr);
				i--;
				p++;
			}
			while(y < HEIGHT)
			{
				my_mlx_pixel_put(img, x, y, l);
				y++;
			}
		}
		x++;
		p = 0;
		y = 0;
		y += k;
		i += k;
		k++;
		if (k == 800)
		{
			t = l;
			l = lr;
			lr = t;
			k = 0;
		}
	}
	mlx_clear_window(vars->mlx, vars->win);
	mlx_put_image_to_window(vars->mlx, vars->win, img->img_ptr, 0, 0);
}
