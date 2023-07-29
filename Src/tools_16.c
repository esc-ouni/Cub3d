/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_16.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:23:31 by idouni            #+#    #+#             */
/*   Updated: 2023/07/26 10:53:32 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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

t_data	*draw_2d_map(t_player *plyr)
{
	int		i;
	int		color;
	t_data	*img;

	i = 0;
	img = NULL;
	color = M_BLACK;
	plyr->v->m_w = ft_strlen(plyr->v->map[0]);
	while (plyr->v->map[i])
	{
		if (ft_strlen(plyr->v->map[i]) > plyr->v->m_w)
			plyr->v->m_w = ft_strlen(plyr->v->map[i]);
		i++;
	}
	plyr->v->m_h = i;
	if ((plyr->v->m_w * M_B >= plyr->width) || \
	(plyr->v->m_h * M_B >= plyr->height))
		exit_with_err(plyr, MAP);
	return (creat_tmap(plyr));
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

static int	check(t_player *plyr, int nb, int s)
{
	if (nb > 255 || s == -1)
		exit_with_err(plyr, PARSE);
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
			exit_with_err(plyr, PARSE);
		r = r * 10 + (str[i] - 48);
		r = check(plyr, r, s);
		i++;
	}
	return (r * s);
}
