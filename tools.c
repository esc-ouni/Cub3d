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
		move_up(vars);
	else if (key == K_DN)
		move_dn(vars);
	else if (key == K_R)
		move_rg(vars);
	else if (key == K_L)
		move_lf(vars);
	return(0);
}

void	move_up(t_vars *vars)
{
}
void	move_dn(t_vars *vars)
{
}
void	move_rg(t_vars *vars)
{
}

void	move_lf(t_vars *vars)
{
}

void	draw_2d_map(t_vars *vars)
{
	t_data	*map;
	map = new_image(vars);
	mlx_clear_window(vars->mlx, vars->win);
	mlx_put_image_to_window(vars->mlx, vars->win, map->img_ptr, 0, 0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	(void)color;
	char *tmp;

	tmp = data->img_addr;
	if(!tmp)
		exit(EXIT_FAILURE);
	tmp = tmp + (y * data->size_line) + ((data->byte_pixel) * x);
	*(int *)tmp = color;
}

