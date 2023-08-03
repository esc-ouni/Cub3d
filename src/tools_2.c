/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:54:41 by idouni            #+#    #+#             */
/*   Updated: 2023/07/24 18:43:51 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	correct(int *b, int *r, int *g)
{
	if ((*b) < 0)
		(*b) = 0;
	if ((*r) < 0)
		(*r) = 0;
	if ((*g) < 0)
		(*g) = 0;
}

int	darken_color(int color, int amount)
{
	int	r;
	int	g;
	int	b;

	amount /= 2;
	r = 0;
	g = 0;
	b = 0;
	b |= (unsigned char)color;
	color >>= 8;
	g |= (unsigned char)color;
	color >>= 8;
	r |= (unsigned char)color;
	b -= amount;
	r -= amount;
	g -= amount;
	correct(&b, &r, &g);
	color = 0;
	color |= r;
	color <<= 8;
	color |= g;
	color <<= 8;
	color |= b;
	return (color);
}

char	*get_texture(t_player *plyr, t_ray ray)
{
	char	*s;

	s = NULL;
	if (ray.side == SOUTH)
		s = plyr->v->so->img_addr;
	else if (ray.side == NORTH)
		s = plyr->v->no->img_addr;
	else if (ray.side == EAST)
		s = plyr->v->ea->img_addr;
	else if (ray.side == WEST)
		s = plyr->v->we->img_addr;
	return (s);
}

int	get_color_from_tex(t_player *plyr, char *s, t_ray ray)
{
	int		color;
	char	*tmp;

	if (ray.tex_y >= BLOCK || ray.tex_x >= BLOCK)
		return (0);
	tmp = (s + (ray.tex_y * plyr->v->so->size_line) + \
	(ray.tex_x * plyr->v->so->byte_pixel));
	if (tmp)
	{
		color = *(int *)tmp;
		color = darken_color(color, (float )(ray.length * 255) / (BLOCK * 60));
		return (color);
	}
	return (0);
}

void	draw_wall_part(t_player *plyr, t_data *p_img, t_ray ray, int x_index)
{
	int		i;
	int		start;
	float	w_heig;

	w_heig = plyr->height / (ray.length * trigo(ray.angle - plyr->angle, \
	COS)) * (BLOCK * 1.7);
	start = (plyr->height / 2) - (w_heig / 2);
	i = 0;
	while (i < w_heig)
	{
		if (start + i > 0 && start + i < plyr->height)
		{
			ray.tex_y = i * (BLOCK / w_heig);
			plyr->color = get_color_from_tex(plyr, get_texture(plyr, ray), ray);
			plyr->t_img = p_img;
			my_mlx_pixel_put(plyr, x_index, start + i, plyr->color);
		}
		if (start + i >= plyr->height)
			return ;
		i++;
	}
}
