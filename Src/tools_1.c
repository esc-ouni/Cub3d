/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:54:38 by idouni            #+#    #+#             */
/*   Updated: 2023/07/24 12:16:16 by idouni           ###   ########.fr       */
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

void	update_degree(t_player *plyr, float deg_angle)
{
	deg_angle = deg_to_rad(deg_angle);
	plyr->angle += deg_angle;
	if (plyr->angle >= (2 * M_PI))
		plyr->angle -= 2 * M_PI;
	else if (plyr->angle <= 0)
		plyr->angle += 2 * M_PI;
}

void	m_map(t_player *plyr)
{
	if (plyr->m == 1)	
		plyr->m = 0;
	else
		plyr->m = 1;
	update_scene(plyr);
}

int	handlerp(int key, t_player *plyr)
{
	if (key == 53 || key == 17)
	{
		destroy_prev_imges(plyr);
		destroy_fix_imges(plyr);
		ft_collectorclear(plyr->v->collector, ALL);
	}
	else if (key == 259)
		return (0);
	else if (key == 46)
		m_map(plyr);
	else if (key == M_UP)
		plyr->w = 1;
	else if (key == M_DN)
		plyr->w = -1;
	else if (key == M_RG)
		plyr->d = 1;
	else if (key == M_LF)
		plyr->d = -1;
	else if (key == K_L)
		plyr->rl = 1;
	else if (key == K_R)
		plyr->rl = -1;
	return (0);
}

int	handlerr(int key, t_player *plyr)
{
	if (key == 259)
	{
		plyr->w = 0;
		plyr->d = 0;
		plyr->rl = 0;
	}
	else if (key == 53)
	{
		destroy_prev_imges(plyr);
		destroy_fix_imges(plyr);
		ft_collectorclear(plyr->v->collector, ALL);
		exit(0);
	}
	else if (key == M_UP || key == M_DN)
		plyr->w = 0;
	else if (key == M_RG || key == M_LF)
		plyr->d = 0;
	else if (key == K_R || key == K_L)
		plyr->rl = 0;
	return (0);
}

void	draw_wall(t_player *plyr, t_data *mapp, int x, int y)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	x *= M_B;
	y *= M_B;
	plyr->t_img = mapp;
	while (i < M_B)
	{
		while (j < M_B)
		{
			my_mlx_pixel_put(plyr, x + i, y + j, M_BLACK);
			j++;
		}
		i++;
		j = 0;
	}
}
void	draw_nwall(t_player *plyr, t_data *mapp, int x, int y)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	x *= M_B;
	y *= M_B;
	plyr->t_img = mapp;
	while (i < M_B)
	{
		while (j < M_B)
		{
			my_mlx_pixel_put(plyr, x + i, y + j, M_WHITE);
			j++;
		}
		i++;
		j = 0;
	}
}

int	mouse_movement(int x, int y, t_player *plyr)
{
	static int	last_pos;

	(void)y;
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		if (x > last_pos)
		{
			update_degree(plyr, ((x - last_pos) * (360.0/WIDTH)));
			updateAndRenderScene(plyr);
			last_pos = x;
		}
		else if (x < last_pos)
		{
			update_degree(plyr, ((x - last_pos) * (360.0/WIDTH)));
			updateAndRenderScene(plyr);
			last_pos = x;
		}
	}
	return (0);
}

t_data	*draw_cf(t_player *plyr)
{
	int		ix;
	int		iy;
	int		color;
	t_data	*mapp;

	color = BLACK;
	ix = 0;
	iy = 0;
	mapp = new_image(plyr->v, WIDTH, HEIGHT, NTMP);
	plyr->t_img = mapp;
	while (ix < WIDTH)
	{
		color = plyr->v->c_color;
		while (iy < HEIGHT)
		{
			my_mlx_pixel_put(plyr, ix, iy, color);
			if (iy == HEIGHT/2)
				color = plyr->v->f_color;
			iy++;
		}
		iy = 0;
		ix++;
	}
	return (mapp);
}

t_data	*creat_tmap(t_player *plyr)
{
	int		ix;
	int		iy;
	t_data	*img;

	ix = 0;
	iy = 0;
	img = NULL;
	img = new_image(plyr->v, plyr->v->m_w * M_B, plyr->v->m_h * M_B, NTMP);
	img = ft_transparency(plyr, img, plyr->v->m_w * M_B, plyr->v->m_h * M_B);
	while (plyr->v->map[iy])
	{
		ix = 0;
		while (plyr->v->map[iy][ix])
		{
			if (plyr->v->map[iy][ix] == '1')
				draw_wall(plyr, img, ix, iy);
			else if (plyr->v->map[iy][ix] != '1' && plyr->v->map[iy][ix] != ' ')
				draw_nwall(plyr, img, ix, iy);
			ix++;
		}	
		iy++;
	}
	return (img);
}

t_data	*draw_2d_map(t_player *plyr)
{
	int		i;
	int		color;
	t_data	*img;

	i = 0;
	img = NULL;
	color = M_BLACK;
	plyr->v->m_w = ft_strlen(plyr->v->map[0]);
	while (plyr->v->map[i])
	{
		if (ft_strlen(plyr->v->map[i]) > plyr->v->m_w)
			plyr->v->m_w = ft_strlen(plyr->v->map[i]);
		i++;
	}
	plyr->v->m_h = i;
	if ((plyr->v->m_w * M_B >= WIDTH) || \
	(plyr->v->m_h * M_B >= HEIGHT))
		exit_with_err(plyr->v->collector, MAP);
	return (creat_tmap(plyr));
}
