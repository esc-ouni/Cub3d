#include "Cub.h"

int ft_ext(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	ft_destroy_all_images(vars);
	ft_collectorclear(vars->collector);
	exit(0);
}

int	handler(int key, t_vars *vars)
{
	if (key == 53 || key == 17)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		ft_destroy_all_images(vars);
		ft_collectorclear(vars->collector);
		exit(0);
	}
	// else if (key == K_UP)
	// 	vars->y += d;
	// else if (key == K_DN)
	// 	vars->y -= d;
	// else if (key == K_R)
	// 	vars->x += d;
	// else if (key == K_L)
	// 	vars->x -= d;
	return(0);
}