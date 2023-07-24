/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_15.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:23:31 by idouni            #+#    #+#             */
/*   Updated: 2023/07/24 15:55:14 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

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

void	check_vergs(t_player *plyr, char *s)
{
	if (!ft_strchr(s, ','))
		exit_with_err(plyr->v->collector, PARSE);
	else if (ft_strchr(ft_strchr(ft_strchr(s, ',') + 1, ',') + 1, ','))
		exit_with_err(plyr->v->collector, PARSE);
	else if (ft_strchr(ft_strchr(s, ',') + 1, ','))
		return ;
	else
		exit_with_err(plyr->v->collector, PARSE);
}

int extract_color(t_player *plyr, char *color)
{
	int		i;
	char	**s;
	int		color_c;

	i = 0;
	color_c = 0;
	color = ft_mstrtrim(plyr->v, color, " ", TMP);
	check_vergs(plyr, color);
	s = ft_msplit(plyr->v, color, ',', TMP);
	while (s[i])
		i++;
	if (i != 3)
		exit_with_err(plyr->v->collector, PARSE);
	color_c = ft_atoi(plyr->v->collector, ft_mstrtrim(plyr->v, *s, " ", TMP));
	color_c <<= 8;
	s++;
	color_c |= ft_atoi(plyr->v->collector, ft_mstrtrim(plyr->v, *s, " ", TMP));
	color_c <<= 8;
	s++;
	color_c |= ft_atoi(plyr->v->collector, ft_mstrtrim(plyr->v, *s, " ", TMP));
	return (color_c);
}

int	get_map_indx(t_player *plyr, int fd, int i, char *s)
{
	while ((s = get_next_line(fd)))
	{
		if (ft_strnstr(s, "NO", 2))
			plyr->v->no_c = ft_mstrdup(plyr->v->collector, ft_mstrtrim(plyr->v, s+2, " ", TMP), TMP);
		else if (ft_strnstr(s, "SO", 2))
			plyr->v->so_c = ft_mstrdup(plyr->v->collector, ft_mstrtrim(plyr->v, s+2, " ", TMP), TMP);
		else if (ft_strnstr(s, "WE", 2))
			plyr->v->we_c = ft_mstrdup(plyr->v->collector, ft_mstrtrim(plyr->v, s+2, " ", TMP), TMP);
		else if (ft_strnstr(s, "EA", 2))
			plyr->v->ea_c = ft_mstrdup(plyr->v->collector, ft_mstrtrim(plyr->v, s+2, " ", TMP), TMP);
		else if (ft_strnstr(s, "F", 1))
			plyr->v->f_color = extract_color(plyr, ft_mstrtrim(plyr->v, s+1, " ", TMP));
		else if (ft_strnstr(s, "C", 1))
			plyr->v->c_color = extract_color(plyr, ft_mstrtrim(plyr->v, s+1, " ", TMP));
		else if (ft_strnstr(s, "1", ft_strlen(s)))
		{
			free(s);
			return (i);
		}
		free(s);
		i++;
		s = NULL;
	}
	return (0);
}
