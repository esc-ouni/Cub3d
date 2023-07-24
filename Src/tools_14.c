/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_14.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:23:31 by idouni            #+#    #+#             */
/*   Updated: 2023/07/24 14:59:29 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

void	void_check_middle(t_player *plyr, char **map)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (map[y])
	{
		if ((map[y][0] != '1' && map[y][0] != ' ') || (map[y][ft_strlen(map[y]) \
		- 1] != '1' && map[y][ft_strlen(map[y]) - 1] != ' '))
			exit_with_err(plyr->v->collector, PARSE);
		y++;
	}
}

void	check_mapa(t_player *plyr, char **map)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	void_check_middle(plyr, map);
	while (map[y][x])
	{
		if (map[y][x] != '1' && map[y][x] != ' ')
			exit_with_err(plyr->v->collector, PARSE);
		x++;
	}
	while (map[y])
		y++;
	y--;
	x = 0;
	while (map[y][x])
	{
		if (map[y][x] != '1' && map[y][x] != ' ')
			exit_with_err(plyr->v->collector, PARSE);
		x++;
	}
}

void	check_mapb_t(t_player *plyr, char **map, int *chr, int *c)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (map[y])
	{
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'E' || \
			map[y][x] == 'W' || map[y][x] == 'S')
			{
				plyr->p_x = (float )(x * BLOCK) + (BLOCK / 2);
				plyr->p_y = (float )(y * BLOCK) + (BLOCK / 2);
				(*chr) = map[y][x];
				(*c)++;
			}
			else if (map[y][x] != '0' && map[y][x] != '1' && map[y][x] != ' ')
				exit_with_err(plyr->v->collector, PARSE);
			x++;
		}
		y++;
		x = 0;
	}
}

void	check_mapb(t_player *plyr, char **map)
{
	int	c;
	int	chr;

	chr = 0;
	c = 0;
	check_mapb_t (plyr, map, &chr, &c);
	if (c != 1)
		exit_with_err (plyr->v->collector, PARSE);
	if (chr == 'N')
		plyr->angle = 3 * (M_PI / 2);
	else if (chr == 'E')
		plyr->angle = 0;
	else if (chr == 'S')
		plyr->angle = (M_PI / 2);
	else if (chr == 'W')
		plyr->angle = M_PI;
}

void	check_map(t_player *plyr, char **map)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	check_mapa(plyr, map);
	check_mapb(plyr, map);
	while (map[y])
	{
		while (map[y][x])
		{
			if (map[y][x] == '0')
				point_surronded(plyr, map, y, x);
			else if ((map[y][x] == 'N' || map[y][x] == 'S' || \
			map[y][x] == 'E' || map[y][x] == 'W'))
				point_surronded(plyr, map, y, x);
			x++;
		}
		y++;
		x = 0;
	}
}
