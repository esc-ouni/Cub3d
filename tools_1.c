#include "Cub.h"

int	handler(int key, t_vars *vars)
{
	
	static int px;
	static int py;
	static int r = 10;

	if (key == 53 || key == 17)
	{
		ft_destroy_all_images(vars);
		ft_collectorclear(vars->collector, ALL);
		exit(0);
	}
	if (key == K_R)
		update_scene(player);
	if (key == K_L)
		update_scene(player);
	if (key == M_RG)
		update_scene(player);
	if (key == M_DN)
		update_scene(player);
	if (key == M_LF)
		update_scene(player);
	if (key == M_UP)
		update_scene(player);
	return(0);
}

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

void	draw_wall(t_data *mapp, int x, int y)
{
	int	i = 0;
	int	j = 0;

	x *= BLOCK;
	y *= BLOCK;
	while(i + 1 < BLOCK)
	{
		while(j + 1 < BLOCK)
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


	x *= BLOCK;
	y *= BLOCK;
	while(i + 1< BLOCK)
	{
		while(j + 1< BLOCK)
		{
			my_mlx_pixel_put(mapp, x + i, y + j, WHITE);
			if(j == (BLOCK - 1))
				my_mlx_pixel_put(mapp, x + i, y + j, BLACK);
			j++;
		}
		i++;
		j = 0;
	}
}

t_data	*draw_2d_map(t_vars *vars)
{
	int		ix;
	int		iy;
	char	**map;
	t_data	*mapp;

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
	// vars->map_ptr = mapp;
	return (mapp);
}

void update_scene(t_player *player)
{
	t_data *p_img;

	p_img = dra
}