/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:54:51 by idouni            #+#    #+#             */
/*   Updated: 2023/07/26 10:53:32 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_ext(t_player *plyr)
{
	destroy_prev_imges(plyr);
	destroy_fix_imges(plyr);
	ft_collectorclear(plyr, ALL);
	exit(0);
}

float	deg_to_rad(float angle)
{
	angle = (angle * M_PI / 180);
	return (angle);
}

float	rad_to_deg(float angle)
{
	angle = (angle * 180 / M_PI);
	return (angle);
}

void	rotate_vector(t_vector *direction, float angle)
{
	angle = deg_to_rad(angle);
	direction->x = ((direction->x * trigo(angle, COS)) - \
	(direction->y * trigo(angle, SIN)));
	direction->y = ((direction->x * trigo(angle, SIN)) + \
	(direction->y * trigo(angle, COS)));
}

void	my_mlx_pixel_put(t_player *plyr, int x, int y, int color)
{
	char	*tmp;

	tmp = plyr->t_img->img_addr;
	if (!tmp)
		exit_with_err(plyr, MLX);
	tmp = tmp + (y * plyr->t_img->size_line) + ((plyr->t_img->byte_pixel) * x);
	if (tmp)
		*(int *)tmp = color;
}
