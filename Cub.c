#include "Cub.h"

void	draw_in_image(t_vars *vars)
{
	int t = 0;
	int i = 0;
	int k = 0;
	int x = 0;
	int p = 0;
	int y = 0;
	int lr = 0xFF0000;
	int l = 0x0300FF;

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

int main(int argc, char const *argv[])
{
	(void)argc;
	(void)argv;
	t_collector *collector;
	t_img_collector *img_collector;
	t_vars 		*vars;
	
	collector = NULL;
	img_collector = NULL;

	vars = NULL;
	vars = h_malloc(&collector, sizeof(t_vars), vars);
	vars->img_collector = &img_collector;
	vars->collector = &collector;
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "Cub");
	if(!vars->mlx || !vars->win)
	{
		write (2, "\033[0;32mMLX_FAILED\033[0;37m\n", 29);
		ft_destroy_all_images(vars);
		ft_collectorclear(vars->collector);
		exit (1);
	}
	draw_in_image(vars);
	mlx_hook(vars->win, 17, 0, ft_ext, vars);
	mlx_key_hook(vars->win, handler, vars);
	mlx_loop(vars->mlx);
	return 0;
}
