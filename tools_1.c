#include "Cub.h"

void update_scene(t_player *player)
{
	t_data *p_img;
	t_ray  **ray;

	ray = NULL;
	ray = h_malloc(player->vars->collector, (sizeof(t_ray *) * WIDTH) + 1, ray, NTMP);
	p_img = draw_2d_map(player);
	p_img = draw_player(player, p_img);
	mlx_clear_window(player->vars->mlx, player->vars->win);
	mlx_put_image_to_window(player->vars->mlx, player->vars->win, p_img->img_ptr, 0, 0);
	p_img = cast_rays(player, p_img, ray);
	// p_img = draw_3d_map(player, p_img, ray);

}

void move_right(t_player *player)
{
    player->p_x += 10 * cos(player->angle);
    player->p_y += 10 * sin(player->angle);
	if (check_collision(player, 10, 0))
	{
		update_scene(player);
	}
}
void move_left(t_player *player)
{
    player->p_x += 10 * cos(player->angle);
    player->p_y += 10 * sin(player->angle);
	if (check_collision(player, -10, 0))
	{
		update_scene(player);
	}
}
void move_up(t_player *player)
{
	int x = 10 * cos(player->angle);
	int y = 10 * sin(player->angle);

	if (check_collision(player, x, y))
	{
		player->p_x += x;
		player->p_y += y;
		update_scene(player);
	}
}
void move_down(t_player *player)
{
	int x = 10 * cos(player->angle);
	int y = 10 * sin(player->angle);

	if (check_collision(player, -x, -y))
	{
		player->p_x -= x;
		player->p_y -= y;
		update_scene(player);
	}
}

void	update_degree(t_player *player, float deg_angle)
{
	deg_angle = deg_to_rad(deg_angle);
	player->angle += deg_angle;
	if (player->angle >= (2 * M_PI))
		player->angle -= 2 * M_PI;
	else if (player->angle < 0)
		player->angle += 2 * M_PI;
}


void rotate_right(t_player *player)
{
	rotate_vector(player->direction, 15);
	update_degree(player, 15);
	update_scene(player);
}
void rotate_left(t_player *player)
{
	rotate_vector(player->direction, -15);
	update_degree(player, -15);
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

int mouse_movement(int x, int y, t_player *player)
{
	static int last_pos;

	if (x >= 0 && x <= WIDTH)
	{
		if (x >= last_pos)
		{
			rotate_vector(player->direction, ((x - last_pos)/5));
			update_scene(player);
			last_pos = x;
		}
		else if (x < last_pos)
		{
			rotate_vector(player->direction, ((x - last_pos)/5));
			update_scene(player);
			last_pos = x;
		}
	}
	return (0);
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
