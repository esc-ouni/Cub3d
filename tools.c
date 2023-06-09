#include "Cub.h"

int ft_ext(t_vars *vars)
{
	ft_destroy_all_images(vars);
	ft_collectorclear(vars->collector);
	exit(0);
}

int	handler(int key, t_vars *vars)
{
	static int q;
	if (key == 53 || key == 17)
	{
		ft_destroy_all_images(vars);
		ft_collectorclear(vars->collector);
		exit(0);
	}
	else if (key == K_UP)
		draw_in_image(vars, q);
	else if (key == K_DN)
		draw_in_image(vars, q);
	else if (key == K_R)
		draw_in_image(vars, q);
	else if (key == K_L)
		draw_in_image(vars, q);
	if(!q)
		q = 1;
	else
		q = 0;
	return(0);
}

void	draw_in_image(t_vars *vars, int r)
{
	int t = 0;
	int i = 0;
	int k = 0;
	int x = 0;
	int p = 0;
	int y = 0;
	int lr = 0xFF0000;
	int l = 0x0300FF;

	if(r)
	{
		l = 0xFF0000;
		lr = 0x0300FF;
	}
	mlx_clear_window(vars->mlx, vars->win);
	while(x < WIDTH)
	{
		while(y < HEIGHT)
		{
			while (i)
			{
				mlx_pixel_put(vars->mlx, vars->win, x, p , lr);
				i--;
				p++;
			}
			while(y < HEIGHT)
			{
				mlx_pixel_put(vars->mlx, vars->win, x, y, l);
				y++;
			}
			y++;
		}
		x++;
		p = 0;
		y = 0;
		y += k;
		i += k;
		k++;
		if (k == 799)
		{
			t = l;
			l = lr;
			lr = t;
			k = 0;
		}
	}
}
