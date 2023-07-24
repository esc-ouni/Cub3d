/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:54:38 by idouni            #+#    #+#             */
/*   Updated: 2023/07/24 13:27:18 by idouni           ###   ########.fr       */
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
