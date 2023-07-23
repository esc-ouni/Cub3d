/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:54:38 by idouni            #+#    #+#             */
/*   Updated: 2023/07/23 14:52:04 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

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
	else if (player->angle <= 0)
		player->angle += 2 * M_PI;
}

void	m_map(t_player *player)
{
	if (player->m == 1)	
		player->m = 0;
	else
		player->m = 1;
	update_scene(player);
}

int	handlerp(int key, t_player *player)
{
	if (key == 53 || key == 17)
	{
		destroy_prev_imges(player);
		destroy_fix_imges(player);
		ft_collectorclear(player->vars->collector, ALL);
	}
	if (key == 46)
		m_map(player);
	if (key == M_UP)
		player->w = 1;
	if (key == M_DN)
		player->w = -1;
	if (key == M_RG)
		player->d = 1;
	if (key == M_LF)
		player->d = -1;
	if (key == K_L)
		player->rl = 1;
	if (key == K_R)
		player->rl = -1;
	if (key == 259)
	{
		player->w = 0;
		player->d = 0;
		player->rl = 0;
	}
	return (0);
}

int	handlerr(int key, t_player *player)
{
	if (key == 259)
	{
		player->w = 0;
		player->d = 0;
		player->rl = 0;
	}
	if (key == 53)
	{
		destroy_prev_imges(player);
		destroy_fix_imges(player);
		ft_collectorclear(player->vars->collector, ALL);
		exit(0);
	}
	if (key == M_UP || key == M_DN)
		player->w = 0;
	if (key == M_RG || key == M_LF)
		player->d = 0;
	if (key == K_R || key == K_L)
		player->rl = 0;
	return (0);
}

void	draw_wall(t_player *player, t_data *mapp, int x, int y)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	x *= M_BLOCK;
	y *= M_BLOCK;
	player->t_img = mapp;
	while (i < M_BLOCK)
	{
		while (j < M_BLOCK)
		{
			my_mlx_pixel_put(player, x + i, y + j, M_BLACK);
			j++;
		}
		i++;
		j = 0;
	}
}
void	draw_nwall(t_player *player, t_data *mapp, int x, int y)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	x *= M_BLOCK;
	y *= M_BLOCK;
	player->t_img = mapp;
	while (i < M_BLOCK)
	{
		while (j < M_BLOCK)
		{
			my_mlx_pixel_put(player, x + i, y + j, M_WHITE);
			// if(j == (M_BLOCK - 1)|| i == 0)
			// 	my_mlx_pixel_put(player, mapp, x + i, y + j, M_BLACK);
			j++;
		}
		i++;
		j = 0;
	}
}

int	mouse_movement(int x, int y, t_player *player)
{
	static int	last_pos;

	(void)y;
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		if (x > last_pos)
		{
			update_degree(player, ((x - last_pos) * (360.0/WIDTH)));
			updateAndRenderScene(player);
			last_pos = x;
		}
		else if (x < last_pos)
		{
			update_degree(player, ((x - last_pos) * (360.0/WIDTH)));
			updateAndRenderScene(player);
			last_pos = x;
		}
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
	player->t_img = mapp;
	while (ix < WIDTH)
	{
		color = player->vars->c_color;
		while (iy < HEIGHT)
		{
			my_mlx_pixel_put(player, ix, iy, color);
			if (iy == HEIGHT/2)
				color = player->vars->f_color;
			iy++;
		}
		iy = 0;
		ix++;
	}
	return (mapp);
}

t_data	*creat_tmap(t_player *player)
{
	int		ix;
	int		iy;
	t_data	*img;

	ix = 0;
	iy = 0;
	img = NULL;
	img = new_image(player->vars, player->vars->map_w * M_BLOCK, player->vars->map_h * M_BLOCK, NTMP);
	img = ft_transparency(player, img, player->vars->map_w * M_BLOCK, player->vars->map_h * M_BLOCK);
	while(player->vars->map[iy])
	{
		ix = 0;
		while (player->vars->map[iy][ix])
		{
			if (player->vars->map[iy][ix] == '1')
				draw_wall(player, img, ix, iy);
			else if (player->vars->map[iy][ix] != '1' && player->vars->map[iy][ix] != ' ')
				draw_nwall(player, img, ix, iy);
			ix++;
		}	
		iy++;
	}
	return (img);
}

t_data	*draw_2d_map(t_player *player)
{
	int		i;
	int		color;
	t_data	*img;

	i = 0;
	img = NULL;
	color = M_BLACK;
	player->vars->map_w = ft_strlen(player->vars->map[0]);
	while (player->vars->map[i])
	{
		if (ft_strlen(player->vars->map[i]) > player->vars->map_w)
			player->vars->map_w = ft_strlen(player->vars->map[i]);
		i++;
	}
	player->vars->map_h = i;
	if ((player->vars->map_w * M_BLOCK >= WIDTH) || \
	(player->vars->map_h * M_BLOCK >= HEIGHT))
		exit_with_err(player->vars->collector, MAP);
	return (creat_tmap(player));
}
