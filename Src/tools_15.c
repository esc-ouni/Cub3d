/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_15.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:23:31 by idouni            #+#    #+#             */
/*   Updated: 2023/07/24 17:15:56 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

void	draw_point(t_player *plyr, int x, int y, int color)
{
	int	i;
	int	j;

	i = -2;
	j = -2;
	while (i < 4)
	{
		while (i < 2)
		{
			while (j < 2)
			{
				my_mlx_pixel_put(plyr, x + i, y + j, color);
				j++;
			}
			i++;
			j = -2;
		}
		i++;
	}
}

float	ft_pow(float n)
{
	return (n * n);
}

float	ft_abs(float n)
{
	if (n < 0)
		n = -n;
	return (n);
}

char	**get_map_cont(t_player *plyr, int fd, int t, char **map)
{
	int		i2;
	char	*s;

	i2 = 0;
	s = NULL;
	s = get_next_line(fd);
	while (s)
	{
		if (t <= 0)
		{
			map[i2] = ft_mstrdup(plyr->v->collector, s, NTMP);
			i2++;
		}
		free(s);
		s = NULL;
		s = get_next_line(fd);
		t--;
	}
	map[i2] = NULL;
	return (map);
}

char	**get_map(t_player *plyr, char const *argv[], int t)
{
	int		fd;
	char	**map;

	fd = 0;
	map = NULL;
	map = h_malloc(plyr->v->collector, (count_alloc_size(plyr->v->collector, \
	argv, fd) * sizeof(char *)), map, NTMP);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit_with_err(plyr->v->collector, OPEN);
	return (get_map_cont(plyr, fd, t, map));
}
