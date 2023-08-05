/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_13.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:23:31 by idouni            #+#    #+#             */
/*   Updated: 2023/08/05 17:18:47 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

float	trigo(float angle, t_flag flag)
{
	if (flag == COS)
		return (cos(angle));
	else if (flag == SIN)
		return (sin(angle));
	else if (flag == TAN)
		return (tan(angle));
	return (0);
}

t_vector	*find_horizontal_iterset(t_player *plyr, \
t_ray *ray, t_vector *vector)
{
	if ((ray->angle > 0 && ray->angle < M_PI))
		vector = h_dn_iterset(plyr, ray, vector);
	else if (ray->angle > M_PI && ray->angle < 2 * M_PI)
		vector = h_up_iterset(plyr, ray, vector);
	ray->h_d = sqrt(ft_pow(plyr->v2->x - plyr->p_x) + \
	ft_pow(plyr->v2->y - plyr->p_y));
	return (vector);
}

t_vector	*h_rg_iterset(t_player *plyr, t_ray *ray, t_vector *vector)
{
	ray->dx = plyr->block;
	ray->dy = ray->dx * ray->t1;
	vector->x = (ceil(plyr->p_x / plyr->block) * plyr->block);
	vector->y = plyr->p_y + (ft_abs(plyr->p_x - vector->x) * ray->t1);
	while (!wall_hit_vrg(plyr, (int)vector->x, (int)vector->y))
	{
		vector->x += ray->dx;
		vector->y += ray->dy;
	}
	return (vector);
}

t_vector	*h_lf_iterset(t_player *plyr, t_ray *ray, t_vector *vector)
{
	ray->dx = -plyr->block;
	ray->dy = -(plyr->block * ray->t1);
	vector->x = (floor(plyr->p_x / plyr->block) * plyr->block);
	vector->y = plyr->p_y - (ft_abs(plyr->p_x - vector->x) * ray->t1);
	while (!wall_hit_vlf(plyr, (int)vector->x, (int)vector->y))
	{
		vector->x += ray->dx;
		vector->y += ray->dy;
	}
	return (vector);
}

t_vector	*find_vertical_iterset(t_player *plyr, t_ray *ray, t_vector *vector)
{
	if (((ray->angle > (3 * (M_PI / 2))) && (ray->angle <= 2 * (M_PI))) || \
	(((ray->angle >= 0) && (ray->angle < (M_PI / 2)))))
		vector = h_rg_iterset(plyr, ray, vector);
	else if ((ray->angle > (M_PI / 2)) || (ray->angle < 3 * (M_PI / 2)))
		vector = h_lf_iterset(plyr, ray, vector);
	ray->v_d = sqrt(ft_pow(plyr->v1->x - plyr->p_x) + \
	ft_pow(plyr->v1->y - plyr->p_y));
	return (vector);
}
