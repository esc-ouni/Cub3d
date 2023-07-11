/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:23:31 by idouni            #+#    #+#             */
/*   Updated: 2023/07/11 11:28:31 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

void draw_line(t_player *player, t_data *p_img, int color, int x2, int y2)
{
    int i = 0;

    float dx = x2/5 - (int)player->p_x/5;
    float dy = y2/5 - (int)player->p_y/5;
    float steps = ft_abs(dy);
	if (ft_abs(dx) > ft_abs(dy))
		steps = ft_abs(dx);
    float x_inc = dx / steps;
    float y_inc = dy / steps;

    float x = (int)player->p_x/5;
    float y = (int)player->p_y/5;

    while ( i < steps)
    {
		my_mlx_pixel_put(player, p_img, (int)x, (int)y, color);
        x += x_inc;
        y += y_inc;
        i++;
    }
}