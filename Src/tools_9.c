/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_9.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:23:31 by idouni            #+#    #+#             */
/*   Updated: 2023/07/24 14:06:50 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

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
	if (x > 0 && x < plyr->width && y > 0 && y < plyr->height)
	{
		if (x > last_pos)
		{
			update_degree(plyr, ((x - last_pos) * (360.0/plyr->width)));
			updateAndRenderScene(plyr);
			last_pos = x;
		}
		else if (x < last_pos)
		{
			update_degree(plyr, ((x - last_pos) * (360.0/plyr->width)));
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
	mapp = new_image(plyr->v, plyr->width, plyr->height, NTMP);
	plyr->t_img = mapp;
	while (ix < plyr->width)
	{
		color = plyr->v->c_color;
		while (iy < plyr->height)
		{
			my_mlx_pixel_put(plyr, ix, iy, color);
			if (iy == plyr->height/2)
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
	if ((plyr->v->m_w * M_B >= plyr->width) || \
	(plyr->v->m_h * M_B >= plyr->height))
		exit_with_err(plyr->v->collector, MAP);
	return (creat_tmap(plyr));
}

