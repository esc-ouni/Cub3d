#include "Cub.h"

void move_right(t_player *player)
{
	float angle = up_degree(player->angle, 90);

	int x = 20 * cos(angle);
	int y = 20 * sin(angle);

	if (check_collision(player, x, y))
	{
		player->p_x += x;
		player->p_y += y;
		update_scene(player);
	}
}
void move_left(t_player *player)
{
	float angle = up_degree(player->angle, -90);
	int x = 20 * cos(angle);
	int y = 20 * sin(angle);

	if (check_collision(player, x, y))
	{
		player->p_x += x;
		player->p_y += y;
		update_scene(player);
	}
}
void move_up(t_player *player)
{
	int x = 20 * cos(player->angle);
	int y = 20 * sin(player->angle);

	if (check_collision(player, x, y))
	{
		player->p_x += x;
		player->p_y += y;
		update_scene(player);
	}
}
void move_down(t_player *player)
{
	int x = 20 * cos(player->angle);
	int y = 20 * sin(player->angle);

	if (check_collision(player, -x, -y))
	{
		player->p_x -= x;
		player->p_y -= y;
		update_scene(player);
	}
}

float	up_degree(float angle, float add_angle)
{
	add_angle = deg_to_rad(add_angle);
	angle += add_angle;
	if (angle >= (2 * M_PI))
		angle -= 2 * M_PI;
	else if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
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
	rotate_vector(player->direction, 25.5);
	update_degree(player, 25.5);
	update_scene(player);
}
void rotate_left(t_player *player)
{
	rotate_vector(player->direction, -25.5);
	update_degree(player, -25.5);
	update_scene(player);
}

int	handler(int key, t_player *player)
{
	if (key == 53 || key == 17)
	{
		ft_collectorclear(player->vars->collector, ALL);
		exit(0);
	}
	if (key == M_UP)
		move_up(player);
	if (key == M_DN)
		move_down(player);
	if (key == K_R)
		rotate_right(player);
	if (key == K_L)
		rotate_left(player);
	if (key == M_RG)
		move_right(player);
	if (key == M_LF)
		move_left(player);
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
	(void)y;
	static int last_pos;

	// if (x >= 0 && x <= WIDTH)
	// {
		if (x > last_pos)
		{
			rotate_vector(player->direction, ((x - last_pos)/3));
			update_degree(player, ((x - last_pos)/3));
			update_scene(player);
			last_pos = x;
		}
		else if (x < last_pos)
		{
			rotate_vector(player->direction, ((x - last_pos)/3));
			update_degree(player, ((x - last_pos)/3));
			update_scene(player);
			last_pos = x;
		}
	// }
	return (0);
}


t_data	*draw_2d_map(t_player *player)
{
	int		ix;
	int		iy;
	int		color;
	char	**map;
	t_data	*mapp;

	color = BLACK;
	map = player->vars->map;
	ix = 0;
	iy = 0;
	mapp = new_image(player->vars);
	player->vars->last_img = mapp;
	while (ix < WIDTH)
	{
		color = C_COLOR;
		// if (ix >= 1800)
		while (iy < HEIGHT)
		{
			my_mlx_pixel_put(mapp, ix, iy, color);
			if (iy == HEIGHT/2)
				color = F_COLOR;
			iy++;
		}
		iy = 0;
		ix++;
	}
	// ix = 0;
	// iy = 0;
	// while(map[iy])
	// {
	// 	while(map[iy][ix])
	// 	{
	// 		if (map[iy][ix] == '1')
	// 			draw_wall(mapp, ix, iy);
	// 		else 
	// 			draw_nwall(mapp, ix, iy);
	// 		ix++;
	// 	}	
	// 	iy++;
	// 	ix = 0;
	// }
	return (mapp);
}
