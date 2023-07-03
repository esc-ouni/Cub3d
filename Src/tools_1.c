/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:54:38 by idouni            #+#    #+#             */
/*   Updated: 2023/07/03 13:54:39 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

void move_right(t_player *player)
{
	float angle = up_degree(player->angle, 90);

	int x = 40 * trigo(angle, COS);
	int y = 40 * trigo(angle, SIN);

	if (check_collision(player, x, y))
	{
		player->p_x += x;
		player->p_y += y;
		// update_scene(player);
		updateAndRenderScene(player);

	}
}
void move_left(t_player *player)
{
	float angle = up_degree(player->angle, -90);
	int x = 40 * trigo(angle, COS);
	int y = 40 * trigo(angle, SIN);

	if (check_collision(player, x, y))
	{
		player->p_x += x;
		player->p_y += y;
		// update_scene(player);
		updateAndRenderScene(player);
	}
}
void move_up(t_player *player)
{
	int x = 40 * trigo(player->angle, COS);
	int y = 40 * trigo(player->angle, SIN);

	// printf("x : %f, y : %f\n", player->p_x, player->p_y);
	if (check_collision(player, x, y))
	{
		player->p_x += x;
		player->p_y += y;
		// printf("x : %f, y : %f\n", player->p_x, player->p_y);
		updateAndRenderScene(player);
		// update_scene(player);
	}
}
void move_down(t_player *player)
{
	int x = 40 * trigo(player->angle, COS);
	int y = 40 * trigo(player->angle, SIN);

	if (check_collision(player, -x, -y))
	{
		player->p_x -= x;
		player->p_y -= y;
		// update_scene(player);
		updateAndRenderScene(player);

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
	rotate_vector(player->direction, 15);
	update_degree(player, 15);
	// update_scene(player);
	updateAndRenderScene(player);
}
void rotate_left(t_player *player)
{
	rotate_vector(player->direction, -15);
	update_degree(player, -15);
	// update_scene(player);
	updateAndRenderScene(player);

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

void	draw_wall(t_player *player, t_data *mapp, int x, int y)
{
	int	i = 0;
	int	j = 0;

	x *= M_BLOCK;
	y *= M_BLOCK;
	while(i + 1 < M_BLOCK)
	{
		while(j + 1 < M_BLOCK)
		{
			my_mlx_pixel_put(player, mapp, x + i, y + j, BLACK);
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
	while(i + 1< M_BLOCK)
	{
		while(j + 1 < M_BLOCK)
		{
			my_mlx_pixel_put(player, mapp, x + i, y + j, WHITE);
			if(j == (M_BLOCK - 1))
				my_mlx_pixel_put(player, mapp, x + i, y + j, BLACK);
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
			// update_scene(player);
			updateAndRenderScene(player);

			last_pos = x;
		}
		else if (x < last_pos)
		{
			rotate_vector(player->direction, ((x - last_pos)/3));
			update_degree(player, ((x - last_pos)/3));
			// update_scene(player);
			updateAndRenderScene(player);

			last_pos = x;
		}
	// }
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
	mapp = new_image(player->vars);
	// player->vars->last_img = mapp;
	while (ix < WIDTH)
	{
		color = C_COLOR;
		while (iy < HEIGHT)
		{
			my_mlx_pixel_put(player, mapp, ix, iy, color);
			if (iy == HEIGHT/2)
				color = F_COLOR;
			iy++;
		}
		iy = 0;
		ix++;
	}
	return (mapp);
}

t_data	*draw_2d_map(t_player *player)
{
	int m_w;
	int m_h;
	int		ix;
	int		iy;
	int		color;
	char	**map;
	t_data	*mapp;

	int i = 0;

	color = BLACK;
	map = player->vars->map;
	ix = 0;
	iy = 0;
	m_w = ft_strlen(map[0]);
	while (map[i])
		i++;
	m_h = i;
	// mapp = new_image(player->vars);

	void			*p;
	t_data			*img;

	img = NULL;
	img = h_malloc(player->vars->collector, sizeof(t_data), img, NTMP);
	p = mlx_new_image(player->vars->mlx, m_w * M_BLOCK, m_h * M_BLOCK);
	if (!p)
	{
		if (player->vars->last_img)
			mlx_destroy_image(player->vars->mlx, player->vars->last_img->img_ptr);
		exit_with_err(player->vars->collector, MLX);
	}
	img->img_ptr = p;
	img->img_addr = mlx_get_data_addr(img->img_ptr, &(img->byte_pixel), &(img->size_line), &(img->endian));
	img->byte_pixel /= 8;




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
