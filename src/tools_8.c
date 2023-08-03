/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_8.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:23:31 by idouni            #+#    #+#             */
/*   Updated: 2023/07/24 18:43:51 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	check_ony(t_player *plyr, float y)
{
	if (plyr->v->map[(int)(((plyr->p_y + y) / BLOCK))][(int)((plyr->p_x) / \
	BLOCK)] != '1' && plyr->v->map[(int)(((plyr->p_y + y + plyr->yf / 4) / \
	BLOCK))][(int)((plyr->p_x + plyr->xf / 2) / BLOCK)] != '1')
	{
		if (plyr->v->map[(int)(((plyr->p_y + y + \
		plyr->yf) / BLOCK))][(int)((plyr->p_x + plyr->xf) / BLOCK)] != '1')
			plyr->p_y += y;
	}
}

void	check_onx(t_player *plyr, float x)
{
	if (plyr->v->map[(int)((plyr->p_y) / BLOCK)][(int)((plyr->p_x + x) / \
	BLOCK)] != '1' && plyr->v->map[(int)((plyr->p_y + plyr->yf / 4) / \
	BLOCK)][(int)((plyr->p_x + x + plyr->xf / 2) / BLOCK)] != '1')
	{
		if (plyr->v->map[(int)((plyr->p_y + plyr->yf) / \
		BLOCK)][(int)((plyr->p_x + x + plyr->xf) / BLOCK)] != '1')
			plyr->p_x += x;
	}
}

void	check_collision(t_player *plyr, float x, float y)
{
	if (y < 0)
		plyr->yf *= -1;
	if (x < 0)
		plyr->xf *= -1;
	check_onx(plyr, x);
	check_ony(plyr, y);
	plyr->xf = (BLOCK / 4);
	plyr->yf = (BLOCK / 4);
}
