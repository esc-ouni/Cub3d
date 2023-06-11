#include "Cub.h"

void	draw_wall(t_data *mapp, int x, int y)
{
	int	i = 0;
	int	j = 0;

	x *= 50;
	y *= 50;
	while(i + 1 < 50)
	{
		while(j + 1 < 50)
		{
			my_mlx_pixel_put(mapp, x + i, y + j, BLACK);
			j++;
		}
		i++;
		j = 0;
	}
}
void	draw_nwall(t_data *mapp, int x, int y)
{
	int	i = 0;
	int	j = 0;


	x *= 50;
	y *= 50;
	while(i + 1< 50)
	{
		while(j + 1< 50)
		{
			my_mlx_pixel_put(mapp, x + i, y + j, WHITE);
			if(j == 49)
				my_mlx_pixel_put(mapp, x + i, y + j, BLACK);
			j++;
		}
		i++;
		j = 0;
	}
}

void	draw_2d_map(t_vars *vars)
{
	int		ix;
	int		iy;
	t_data	*mapp;
	char	**map;

	map = vars->map;
	ix = 0;
	iy = 0;
	mapp = new_image(vars);
	while(map[iy])
	{
		while(map[iy][ix])
		{
			if (map[iy][ix] == '1')
				draw_wall(mapp, ix, iy);
			else 
				draw_nwall(mapp, ix, iy);
			ix++;
		}	
		iy++;
		ix = 0;
	}
	mlx_clear_window(vars->mlx, vars->win);
	mlx_put_image_to_window(vars->mlx, vars->win, mapp->img_ptr, 0, 0);
}