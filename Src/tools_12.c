/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_12.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:23:31 by idouni            #+#    #+#             */
/*   Updated: 2023/07/24 14:57:16 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

int	wall_hit_hdn(t_player *plyr, int x, int y)
{
	int	m_y;
	int	m_x;

	m_x = ((x) / BLOCK);
	m_y = ((y) / BLOCK);
	if (m_x < 0 || m_y < 0)
		return (1);
	if (m_y >= plyr->v->m_h || m_x >= ft_strlen(plyr->v->map[m_y]))
		return (1);
	if (plyr->v->map[m_y][m_x] != '1')
		return (0);
	return (1);
}

int	wall_hit_vrg(t_player *plyr, int x, int y)
{
	int	m_y;
	int	m_x;

	m_x = ((x) / BLOCK);
	m_y = ((y) / BLOCK);
	if (m_x < 0 || m_y < 0)
		return (1);
	if (m_y >= plyr->v->m_h || m_x >= ft_strlen(plyr->v->map[m_y]))
		return (1);
	if (plyr->v->map[m_y][m_x] != '1')
		return (0);
	return (1);
}

int	wall_hit_vlf(t_player *plyr, int x, int y)
{
	int	m_y;
	int	m_x;

	m_y = ((y) / BLOCK);
	m_x = ((x) / BLOCK) - 1;
	if (m_x < 0 || m_y < 0)
		return (1);
	if (m_y >= plyr->v->m_h || m_x >= ft_strlen(plyr->v->map[m_y]))
		return (1);
	if (plyr->v->map[m_y][m_x] != '1')
		return (0);
	return (1);
}

t_vector	*h_dn_iterset(t_player *plyr, t_ray *ray, t_vector *vector)
{
	ray->dy = -BLOCK;
	ray->dx = (BLOCK / ray->t2);
	vector->y = floor(plyr->p_y / BLOCK) * BLOCK;
	vector->x = plyr->p_x + (plyr->p_y - vector->y) / ray->t2;
	while (!wall_hit_hup(plyr, (int)vector->x, (int)vector->y))
	{
		vector->x += ray->dx;
		vector->y += ray->dy;
	}
	return (vector);
}

t_vector	*h_up_iterset(t_player *plyr, t_ray *ray, t_vector *vector)
{
	ray->dy = BLOCK;
	ray->dx = (ray->dy / ray->t1);
	vector->y = (ceil(plyr->p_y / BLOCK) * BLOCK);
	vector->x = plyr->p_x + ((vector->y - plyr->p_y) / ray->t1);
	while (!wall_hit_hdn(plyr, (int)vector->x, (int)vector->y))
	{
		vector->y += ray->dy;
		vector->x += ray->dx;
	}
	return (vector);
}
