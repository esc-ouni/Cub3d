/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:54:38 by idouni            #+#    #+#             */
/*   Updated: 2023/07/15 10:22:18 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

void move_right(t_player *player)
{
	float angle = up_degree(player->angle, 90);

	int x = MV_SP * trigo(angle, COS);
	int y = MV_SP * trigo(angle, SIN);

	if (check_collision(player, x, y))
		updateAndRenderScene(player);
}
void move_left(t_player *player)
{
	float angle = up_degree(player->angle, -90);
	int x = MV_SP * trigo(angle, COS);
	int y = MV_SP * trigo(angle, SIN);

	if (check_collision(player, x, y))
		updateAndRenderScene(player);
}
void move_up(t_player *player)
{
	int x = MV_SP * trigo(player->angle, COS);
	int y = MV_SP * trigo(player->angle, SIN);

	if (check_collision(player, x, y))
		updateAndRenderScene(player);
}
void move_down(t_player *player)
{
	int x = MV_SP * trigo(player->angle, COS);
	int y = MV_SP * trigo(player->angle, SIN);

	if (check_collision(player, -x, -y))
		updateAndRenderScene(player);
}

float	up_degree(float angle, float add_angle)
{
	add_angle = deg_to_rad(add_angle);
	angle += add_angle;
	if (angle > (2 * M_PI))
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
	update_degree(player, 10);
	updateAndRenderScene(player);
}
void rotate_left(t_player *player)
{
	update_degree(player, -10);
	updateAndRenderScene(player);

}

int	handler(int key, t_player *player)
{
	// printf("%d\n", key);
	if (key == 53 || key == 17)
	{
    	destroy_prev_imges(player);
		destroy_fix_imges(player);
		ft_collectorclear(player->vars->collector, ALL);
		exit(0);
	}
	else if (key == 46)
	{
		if (player->m == 1)	
			player->m = 0;
		else
			player->m = 1;
		updateAndRenderScene(player);
	}
	else if (key == M_UP)
		move_up(player);
	else if (key == M_DN)
		move_down(player);
	else if (key == K_R)
		rotate_right(player);
	else if (key == K_L)
		rotate_left(player);
	else if (key == M_RG)
		move_right(player);
	else if (key == M_LF)
		move_left(player);
	return(0);
}

void	draw_wall(t_player *player, t_data *mapp, int x, int y)
{
	int	i = 0;
	int	j = 0;

	x *= M_BLOCK;
	y *= M_BLOCK;
	while(i < M_BLOCK)
	{
		while(j < M_BLOCK)
		{
			my_mlx_pixel_put(player, mapp, x + i, y + j, M_BLACK);
			j++;
		}
		i++;
		j = 0;
	}
}
void	draw_nwall(t_player *player, t_data *mapp, int x, int y)
{
	int	i = 0;
	int	j = 0;


	x *= M_BLOCK;
	y *= M_BLOCK;
	while(i < M_BLOCK)
	{
		while(j < M_BLOCK)
		{
			my_mlx_pixel_put(player, mapp, x + i, y + j, M_WHITE);
			// if(j == (M_BLOCK - 1))
			// 	my_mlx_pixel_put(player, mapp, x + i, y + j, M_BLACK);
			j++;
		}
		i++;
		j = 0;
	}
}

// int	call_mouse(int x, int y, t_player *player)
// {
// 	// printf()
// 	mlx_hook(player->vars->win, 6, 0, mouse_movement, player);
// }

int mouse_movement(int x, int y, t_player *player)
{
	(void)y;
	static int last_pos;

	if (x > last_pos)
	{
		// rotate_vector(player->direction, ((x - last_pos)/3));
		update_degree(player, ((x - last_pos)/5));
		// update_degree(player, 1);
		updateAndRenderScene(player);
		last_pos = x;
	}
	else if (x < last_pos)
	{
		// rotate_vector(player->direction, ((x - last_pos)/3));
		update_degree(player, ((x - last_pos)/5));
		// update_degree(player, -1);
		updateAndRenderScene(player);
		last_pos = x;
	}
	return (0);
}

t_data	*draw_cf(t_player *player)
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
	mapp = new_image(player->vars, WIDTH, HEIGHT, NTMP);
	while (ix < WIDTH)
	{
		color = player->vars->c_color;
		while (iy < HEIGHT)
		{
			my_mlx_pixel_put(player, mapp, ix, iy, color);
			if (iy == HEIGHT/2)
				color = player->vars->f_color;
			iy++;
		}
		iy = 0;
		ix++;
	}
	return (mapp);
}

t_data	*draw_2d_map(t_player *player)
{
	int 	m_w;
	int 	m_h;
	int		ix;
	int		iy;
	int		color;
	char	**map;
	t_data	*img;

	img = NULL;
	int i = 0;

	color = M_BLACK;
	map = player->vars->map;
	ix = 0;
	iy = 0;
	m_w = ft_strlen(map[0]);
	while (map[i])
	{
		if (ft_strlen(map[i]) > m_w)
			m_w = ft_strlen(map[i]);
		i++;
	}
	m_h = i;
	player->vars->map_w =  m_w;
	player->vars->map_h =  m_h;
	if ((m_w * M_BLOCK >= WIDTH) || (m_h * M_BLOCK >= HEIGHT))
		exit_with_err(player->vars->collector, MAP);
	img = new_image(player->vars, m_w * M_BLOCK, m_h * M_BLOCK, NTMP);
	img = ft_transparency(player, img,  m_w * M_BLOCK, m_h * M_BLOCK);
	while(map[iy])
	{
		ix = 0;
		while(map[iy][ix])
		{
			if (map[iy][ix] == '1')
				draw_wall(player, img, ix, iy);
			else 
				draw_nwall(player, img, ix, iy);
			ix++;
		}	
		iy++;
	}
	
	return (img);
}
