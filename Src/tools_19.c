/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_19.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:23:31 by idouni            #+#    #+#             */
/*   Updated: 2023/07/30 18:14:56 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	check_paths(t_player *plyr)
{
	check_existence(plyr, plyr->v->no_c);
	check_existence(plyr, plyr->v->we_c);
	check_existence(plyr, plyr->v->so_c);
	check_existence(plyr, plyr->v->ea_c);
}

int	hokking(t_player *plyr)
{
	mlx_hook(plyr->v->win, 17, 0, ft_ext, plyr);
	// mlx_hook(plyr->v->win, 4, (1L << 2), m_hookp, plyr);
	// mlx_hook(plyr->v->win, 5, (1L << 3), m_hookr, plyr);
	mlx_hook(plyr->v->win, 6, (1L << 8), mouse_movement, plyr);
	mlx_hook(plyr->v->win, 2, (1L << 0), handlerp, plyr);
	mlx_hook(plyr->v->win, 3, (1L << 1), handlerr, plyr);
	update_params(plyr);
	return (0);
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

void	xpm_failed(t_player *plyr)
{
	(void)plyr;
	write (2, "\033[0;32mError\nMLX_XPM_FAILED\033[0;37m\n", 36);
	exit(0);
}
