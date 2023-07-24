/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:23:31 by idouni            #+#    #+#             */
/*   Updated: 2023/07/24 13:25:10 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

void	free_ntmp(t_collector **collector)
{
	t_ntmp	*node1;
	t_ntmp	*n_node1;

	node1 = (*collector)->ntmp_cltr;
	if (!node1)
		return ;
	while (node1)
	{
		n_node1 = node1->next;
		if (node1->ntmp_addr)
			free(node1->ntmp_addr);
		free(node1);
		node1 = n_node1;
	}
	(*collector)->ntmp_cltr = NULL;
}

void	ft_collectorclear(t_collector **collector, t_flag flag)
{
	if (!(*collector) || !collector)
		return ;
	if (flag == TMP)
		free_tmp(collector);
	else if (flag == NTMP)
		free_ntmp(collector);
	else if (flag == ALL)
	{
		free_tmp(collector);
		free_ntmp(collector);
		free((*collector));
		(*collector) = NULL;
		exit(0);
	}
}

void	head_alloc(t_collector **collector)
{
	(*collector) = malloc(sizeof(t_collector));
	if (*collector)
	{
		(*collector)->tmp_cltr = NULL;
		(*collector)->ntmp_cltr = NULL;
	}
}

void	*h_malloc(t_collector **collector, size_t s, void *p, t_flag flag)
{
	if (!(*collector))
		head_alloc(collector);
	if (flag == TMP)
		tmp_alloc(collector, s, &p);
	else if (flag == NTMP)
		ntmp_alloc(collector, s, &p);
	return (p);
}

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
