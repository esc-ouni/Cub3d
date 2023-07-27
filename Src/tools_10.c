/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_10.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:23:31 by idouni            #+#    #+#             */
/*   Updated: 2023/07/28 00:10:04 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_3d_map(t_player *plyr, t_data *p_img, t_ray *ray)
{
	int	i;

	i = 0;
	while (i < plyr->width)
	{
		draw_wall_part(plyr, p_img, ray[i], i);
		i++;
	}
}

t_data	*ft_transparency(t_player *plyr, t_data *p_img, int width, int height)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	plyr->t_img = p_img;
	while (i < width)
	{
		while (j < height)
		{
			my_mlx_pixel_put(plyr, i, j, TRANS);
			j++;
		}
		i++;
		j = 0;
	}
	return (p_img);
}

void	destroy_fix_imges(t_player *plyr)
{
	if (plyr && plyr->v)
	{
		if (plyr->v->we)
			mlx_destroy_image(plyr->v->mlx, plyr->v->we->img_ptr);
		if (plyr->v->ea)
			mlx_destroy_image(plyr->v->mlx, plyr->v->ea->img_ptr);
		if (plyr->v->so)
			mlx_destroy_image(plyr->v->mlx, plyr->v->so->img_ptr);
		if (plyr->v->no)
			mlx_destroy_image(plyr->v->mlx, plyr->v->no->img_ptr);
		if (plyr->v->fix_img)
			mlx_destroy_image(plyr->v->mlx, plyr->v->fix_img->img_ptr);
		if (plyr->v->m_fix_img)
			mlx_destroy_image(plyr->v->mlx, plyr->v->m_fix_img->img_ptr);
		if (plyr->v->mlx && plyr->v->win)
			mlx_destroy_window(plyr->v->mlx, plyr->v->win);
	}
}

void	destroy_prev_imges(t_player *plyr)
{
	int	i;

	i = 0;
	while (plyr->p[i])
	{
		mlx_destroy_image(plyr->v->mlx, plyr->p[i]);
		plyr->p[i] = NULL;
		i++;
	}
}

void	update_params(t_player *plyr)
{
	if (plyr->w == 1)
		check_collision(plyr, plyr->mv_sp * trigo(plyr->angle, COS), \
		plyr->mv_sp * trigo(plyr->angle, SIN));
	else if (plyr->w == -1)
		check_collision(plyr, -(plyr->mv_sp * trigo(plyr->angle, COS)), \
		-(plyr->mv_sp * trigo(plyr->angle, SIN)));
	else if (plyr->d == 1)
		check_collision(plyr, (plyr->mv_sp / 2) * trigo(up_degree(plyr->angle, \
		90), COS), (plyr->mv_sp / 2) * trigo(up_degree(plyr->angle, 90), SIN));
	else if (plyr->d == -1)
		check_collision(plyr, (plyr->mv_sp / 2) * trigo(up_degree(plyr->angle, \
		-90), COS), (plyr->mv_sp / 2) * \
		trigo(up_degree(plyr->angle, -90), SIN));
	else if (plyr->rl == 1)
		update_degree(plyr, -R_AN);
	else if (plyr->rl == -1)
		update_degree(plyr, R_AN);
	else
		return ;
	update_scene (plyr);
}
