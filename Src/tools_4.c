/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:23:31 by idouni            #+#    #+#             */
/*   Updated: 2023/07/24 10:59:59 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

void	draw_line(t_player *plyr, int color, int x2, int y2)
{
	float	x;
	float	y;
	int		steps;
	float	x_inc;
	float	y_inc;

	x = (x2 / plyr->factor) - (plyr->p_x / plyr->factor);
	y = (y2 / plyr->factor) - (plyr->p_y / plyr->factor);
	steps = ft_abs(y) - 1;
	if (ft_abs(x) > ft_abs(y))
		steps = ft_abs(x) - 1;
	x_inc = (float)(x / steps);
	y_inc = (float)(y / steps);
	x = (plyr->p_x / plyr->factor);
	y = (plyr->p_y / plyr->factor);
	while (steps--)
	{
		my_mlx_pixel_put(plyr, (int)x, (int)y, color);
		x += x_inc;
		y += y_inc;
	}
}
