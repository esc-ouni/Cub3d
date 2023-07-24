/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_8.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:23:31 by idouni            #+#    #+#             */
/*   Updated: 2023/07/24 13:26:47 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

void	check_collision(t_player *plyr, float x, float y)
{
	if (y < 0)
		plyr->yf *= -1;
	if (x < 0)
		plyr->xf *= -1;

	if(plyr->v->map[(int)(((plyr->p_y + y)/BLOCK))][(int)((plyr->p_x)/BLOCK)] != '1' && plyr->v->map[(int)(((plyr->p_y + y + plyr->yf/4)/BLOCK))][(int)((plyr->p_x + plyr->xf/2)/BLOCK)] != '1')
	{
		if (plyr->v->map[(int)(((plyr->p_y + y + plyr->yf)/BLOCK))][(int)((plyr->p_x + plyr->xf)/BLOCK)] != '1')
			plyr->p_y += y;
	}

	if(plyr->v->map[(int)((plyr->p_y)/BLOCK)][(int)((plyr->p_x + x)/BLOCK)] != '1' && plyr->v->map[(int)((plyr->p_y + plyr->yf/4)/BLOCK)][(int)((plyr->p_x + x + plyr->xf/2)/BLOCK)] != '1')
	{
		if(plyr->v->map[(int)((plyr->p_y + plyr->yf)/BLOCK)][(int)((plyr->p_x + x + plyr->xf)/BLOCK)] != '1')
			plyr->p_x += x;
	}
	plyr->xf = (BLOCK / 4);
	plyr->yf = (BLOCK / 4);
}

void draw_point(t_player *plyr, int x, int y, int color)
{
	int i, j;

	i = -2;
	j = -2; 
	while (i < 4)
	{
		while (i < 2)
		{
			while (j < 2)
			{
				my_mlx_pixel_put(plyr, x + i, y + j, color);
				j++;
			}
			i++;
			j = -2;
		}
		i++;
	}
}

float ft_pow(float n)
{
	return (n * n);
}

float 	ft_abs(float  n)
{
	if (n < 0)
		n = -n;
	return (n);
}
