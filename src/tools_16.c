/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_16.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:23:31 by idouni            #+#    #+#             */
/*   Updated: 2023/08/06 09:12:42 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	resizer(t_player *player)
{
	if ((WIDTH > 2560) || (HEIGHT > 1390))
	{
		player->width = 2560;
		player->height = 1390;
	}
	else
	{
		player->width = WIDTH;
		player->height = HEIGHT;
	}
}

t_data	*draw_2d_map(t_player *plyr)
{
	return (creat_tmap(plyr));
}

t_data	*draw_player(t_player *plyr, t_data *p_img)
{
	plyr->t_img = p_img;
	draw_point(plyr, (plyr->p_x / plyr->factor), \
	(plyr->p_y / plyr->factor), BLUE);
	draw_line(plyr, BLUE, plyr->p_x + ((plyr->block / 0.9) * \
	trigo(plyr->angle, COS)) \
	, plyr->p_y + ((plyr->block / 0.9) * trigo(plyr->angle, SIN)));
	return (p_img);
}

static int	check(t_player *plyr, int nb, int s)
{
	(void)plyr;
	if (nb > 255 || s == -1)
		exit_with_err(NULL, PARSE);
	return (nb);
}

int	ft_atoi(t_player *plyr, const char *str)
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
			exit_with_err(NULL, PARSE);
		r = r * 10 + (str[i] - 48);
		r = check(plyr, r, s);
		i++;
	}
	return (r * s);
}
