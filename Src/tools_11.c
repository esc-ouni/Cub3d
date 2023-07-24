/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_11.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:23:31 by idouni            #+#    #+#             */
/*   Updated: 2023/07/24 13:38:28 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

void	show_the_map(t_player *plyr, t_data	*p_r_img)
{
	mlx_put_image_to_window(plyr->v->mlx, plyr->v->win, \
	plyr->v->m_fix_img->img_ptr, 0, 0);
	mlx_put_image_to_window(plyr->v->mlx, plyr->v->win, p_r_img->img_ptr, 0, 0);
}

void	update_scene(t_player *plyr)
{
	t_data	*p_img;
	t_data	*p_r_img;

	destroy_prev_imges(plyr);
	p_img = new_image(plyr->v, WIDTH, HEIGHT, TMP);
	p_r_img = new_image(plyr->v, WIDTH, HEIGHT, TMP);
	p_img = ft_transparency(plyr, p_img, WIDTH, HEIGHT);
	p_r_img = ft_transparency(plyr, p_r_img, WIDTH, HEIGHT);
	draw_player(plyr, p_r_img);
	plyr->ray = cast_rays(plyr, plyr->ray);
	draw_3d_map(plyr, p_img, plyr->ray);
	mlx_clear_window(plyr->v->mlx, plyr->v->win);
	mlx_put_image_to_window(plyr->v->mlx, plyr->v->win, \
	plyr->v->fix_img->img_ptr, 0, 0);
	mlx_put_image_to_window(plyr->v->mlx, plyr->v->win, p_img->img_ptr, 0, 0);
	if (plyr->m)
		show_the_map(plyr, p_r_img);
	plyr->p[0] = p_img->img_ptr;
	plyr->p[1] = p_r_img->img_ptr;
	plyr->p[2] = NULL;
	ft_collectorclear(plyr->v->collector, TMP);
}

float	draw_ray(t_player *plyr, t_ray *ray)
{
	plyr->v1 = find_vertical_iterset(plyr, ray, plyr->v1);
	plyr->v2 = find_horizontal_iterset(plyr, ray, plyr->v2);
	if (ray->v_d < ray->h_d)
	{
		if ((ray->angle <= 2 * M_PI && ray->angle > 3 * M_PI / 2) \
		|| (ray->angle >= 0 && ray->angle < M_PI / 2))
			ray->side = VERT_R;
		else
			ray->side = VERT_L;
		ray->tex_x = (int)plyr->v1->y % BLOCK;
		ray->length = ray->v_d;
	}
	else
	{
		if (ray->angle > 0 && ray->angle < M_PI)
			ray->side = HORZ_D;
		else
			ray->side = HORZ_U;
		ray->tex_x = (int)plyr->v2->x % BLOCK;
		ray->length = ray->h_d;
	}
	return (1);
}

t_ray	*cast_rays(t_player *plyr, t_ray *ray)
{
	int	i;

	i = 0;
	plyr->t_angle = up_degree(plyr->angle, -30);
	while (i < WIDTH)
	{
		ray[i].angle = plyr->t_angle;
		ray[i].t1 = trigo(ray[i].angle, TAN);
		ray[i].t2 = trigo((2 * M_PI) - ray[i].angle, TAN);
		draw_ray(plyr, &ray[i]);
		plyr->t_angle = up_degree(plyr->t_angle, plyr->f_angle);
		i++;
	}
	return (&(ray[0]));
}

int	wall_hit_hup(t_player *plyr, int x, int y)
{
	int	m_y;
	int	m_x;

	m_x = ((x) / BLOCK);
	m_y = ((y) / BLOCK) - 1;
	if (m_x < 0|| m_y < 0)
		return (1);
	if (m_y >= plyr->v->m_h || m_x >= ft_strlen(plyr->v->map[m_y]))
		return (1);
	if (plyr->v->map[m_y][m_x] != '1')
		return (0);
	return (1);
}
