/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:39:03 by idouni            #+#    #+#             */
/*   Updated: 2023/08/06 09:10:00 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	felina(int fd, char *str)
{
	free(str);
	close(fd);
	exit_with_err(NULL, PARSE);
}

void	check_ony(t_player *plyr, float y)
{
	if (plyr->v->map[(int)(((plyr->p_y + y) / \
	plyr->block))][(int)((plyr->p_x) / \
	plyr->block)] != '1' && plyr->v->map[(int)(((plyr->p_y + y + \
	plyr->yf / 4) / \
	plyr->block))][(int)((plyr->p_x + plyr->xf / 2) / plyr->block)] != '1')
	{
		if (plyr->v->map[(int)(((plyr->p_y + y + \
		plyr->yf) / plyr->block))][(int)((plyr->p_x + \
		plyr->xf) / plyr->block)] != '1')
			plyr->p_y += y;
	}
}

void	check_onx(t_player *plyr, float x)
{
	if (plyr->v->map[(int)((plyr->p_y) / plyr->block)][(int)((plyr->p_x + x) / \
	plyr->block)] != '1' && plyr->v->map[(int)((plyr->p_y + plyr->yf / 4) / \
	plyr->block)][(int)((plyr->p_x + x + plyr->xf / 2) / plyr->block)] != '1')
	{
		if (plyr->v->map[(int)((plyr->p_y + plyr->yf) / \
		plyr->block)][(int)((plyr->p_x + x + plyr->xf) / plyr->block)] != '1')
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
	plyr->xf = (plyr->block / 4);
	plyr->yf = (plyr->block / 4);
}
