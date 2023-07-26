/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_15.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:23:31 by idouni            #+#    #+#             */
/*   Updated: 2023/07/26 11:32:00 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_point(t_player *plyr, int x, int y, int color)
{
	int	i;
	int	j;

	i = -(M_B/4);
	j = -(M_B/4);
	while (i < (M_B/2))
	{
		while (i < (M_B/4))
		{
			while (j < (M_B/4))
			{
				my_mlx_pixel_put(plyr, x + i, y + j, color);
				j++;
			}
			i++;
			j = -(M_B/4);
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
	close(fd);
	return (map);
}

char	**get_map(t_player *plyr, char const *argv[], int t)
{
	int		fd;
	char	**map;

	fd = 0;
	map = NULL;
	map = h_malloc(plyr->v->collector, (count_alloc_size(plyr, \
	argv, fd) * sizeof(char *)), map, NTMP);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit_with_err(plyr, OPEN);
	return (get_map_cont(plyr, fd, t, map));
}
