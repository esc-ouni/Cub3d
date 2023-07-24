/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_16.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:23:31 by idouni            #+#    #+#             */
/*   Updated: 2023/07/24 14:33:47 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

void	resizer(t_player *player)
{
	if ((WIDTH > 2880) || (HEIGHT > 1574))
	{
		player->width = 2880;
		player->height = 1574;
	}
	else
	{
		player->width = WIDTH;
		player->height = HEIGHT;
	}
}

t_data	*draw_player(t_player *plyr, t_data *p_img)
{
	plyr->t_img = p_img;
	draw_point(plyr, (plyr->p_x / plyr->factor), \
	(plyr->p_y / plyr->factor), BLUE);
	draw_line(plyr, BLUE, plyr->p_x + ((BLOCK / 0.9) * trigo(plyr->angle, COS)) \
	, plyr->p_y + ((BLOCK / 0.9) * trigo(plyr->angle, SIN)));
	return (p_img);
}

static int	check(t_collector **collector, int nb, int s)
{
	if (nb > 255 || s == -1)
		exit_with_err(collector, PARSE);
	return (nb);
}

int	ft_atoi(t_collector **collector, const char *str)
{
	int					i;
	int					r;
	int					s;

	s = 1;
	r = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] < 48 || str[i] > 57))
			exit_with_err(collector, PARSE);
		r = r * 10 + (str[i] - 48);
		r = check(collector, r, s);
		i++;
	}
	return (r * s);
}