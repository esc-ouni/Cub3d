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
	t_data		*img;

	img = NULL;
	img = h_malloc(vars->collector, sizeof(t_data), img);
	if(r)
	{
		l = 0xFF0000;
		lr = 0x0300FF;
	}
	mlx_clear_window(vars->mlx, vars->win);
	img->img = new_image(vars);
	img->addr = mlx_get_data_addr(img->img, &(img->bits_per_pixel), &(img->line_length), &(img->endian));
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
	mlx_put_image_to_window(vars->mlx, vars->win, img->img, 0, 0);
}

// void	draw_in_image(t_vars *vars, int r)
// {
// 	int t = 0;
// 	int i = 0;
// 	int k = 0;
// 	int x = 0;
// 	int p = 0;
// 	int y = 0;
// 	int lr = 0xFF0000;
// 	int l = 0x0300FF;

// 	if(r)
// 	{
// 		l = 0xFF0000;
// 		lr = 0x0300FF;
// 	}
// 	mlx_clear_window(vars->mlx, vars->win);
// 	while(x < WIDTH)
// 	{
// 		while(y < HEIGHT)
// 		{
// 			while (i)
// 			{
// 				mlx_pixel_put(vars->mlx, vars->win, x, p , lr);
// 				i--;
// 				p++;
// 			}
// 			while(y < HEIGHT)
// 			{
// 				mlx_pixel_put(vars->mlx, vars->win, x, y, l);
// 				y++;
// 			}
// 		}
// 		x++;
// 		p = 0;
// 		y = 0;
// 		y += k;
// 		i += k;
// 		k++;
// 		if (k == 800)
// 		{
// 			t = l;
// 			l = lr;
// 			lr = t;
// 			k = 0;
// 		}
// 	}
// }

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
