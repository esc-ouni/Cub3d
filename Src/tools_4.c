/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:23:31 by idouni            #+#    #+#             */
/*   Updated: 2023/07/23 18:26:15 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

void draw_line(t_player *plyr, int color, int x2, int y2)
{
    int i = 0;

    float  dx = x2/plyr->factor - plyr->p_x/plyr->factor;
    float  dy = y2/plyr->factor - plyr->p_y/plyr->factor;
    float  steps = ft_abs(dy);
	if (ft_abs(dx) > ft_abs(dy))
		steps = ft_abs(dx);
    float  x_inc = dx / steps;
    float  y_inc = dy / steps;

    float  x = plyr->p_x/plyr->factor;
    float  y = plyr->p_y/plyr->factor;
	
    while (i < steps)
    {
		my_mlx_pixel_put(plyr, (int)x, (int)y, color);
        x += x_inc;
        y += y_inc;
        i++;
    }
}
