#include "Cub.h"

void update_scene(t_player *player)
{
	t_data *p_img;

	p_img = draw_2d_map(player);
	p_img = draw_player(player, p_img);
	p_img = cast_rays(player, p_img);
	mlx_clear_window(player->vars->mlx, player->vars->win);
	mlx_put_image_to_window(player->vars->mlx, player->vars->win, p_img->img_ptr, 0, 0);
}

void move_right(t_player *player)
{
	player->p_x += 10;
	update_scene(player);
}
void move_left(t_player *player)
{
	player->p_x -= 10;
	update_scene(player);
}

void rotate_right(t_player *player)
{
	update_scene(player);
}
void rotate_left(t_player *player)
{
	update_scene(player);
}
void move_up(t_player *player)
{
	player->p_y -= 10;
	update_scene(player);
}
void move_down(t_player *player)
{
	player->p_y += 10;
	update_scene(player);
}

int	handler(int key, t_player *player)
{
	static int r = 10;

	if (key == 53 || key == 17)
	{
		ft_destroy_all_images(player->vars);
		ft_collectorclear(player->vars->collector, ALL);
		exit(0);
	}
	if (key == K_R)
		rotate_right(player);
	if (key == K_L)
		rotate_left(player);
	if (key == M_RG)
		move_right(player);
	if (key == M_DN)
		move_down(player);
	if (key == M_LF)
		move_left(player);
	if (key == M_UP)
		move_up(player);
	return(0);
}

void draw_ray(t_data *p_img, t_player *player, t_vector direction)
{
	if ((direction.y == player->p_y) && (direction.x == player->p_x))
		return;
	float i = 0;
	float steps;
	float x_inc;
	float y_inc;
	int	 x = player->p_x;
	int	 y = player->p_y;
	float dy = (direction.y - player->p_y);
	float dx = (direction.x - player->p_x);


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

t_data	*draw_2d_map(t_player *player)
{
	int		ix;
	int		iy;
	char	**map;
	t_data	*mapp;

	map = player->vars->map;
	ix = 0;
	iy = 0;
	mapp = new_image(player->vars);
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
	return (mapp);
}
