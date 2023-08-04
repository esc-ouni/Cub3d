/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_18.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 01:14:23 by msamhaou          #+#    #+#             */
/*   Updated: 2023/08/04 10:40:43 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	check_vergs(t_player *plyr, char *s)
{
	(void)plyr;
	if (!ft_strchr(s, ','))
		exit_with_err(NULL, PARSE);
	else if (ft_strchr(ft_strchr(s, ',') + 1, ','))
	{
		if (ft_strchr(ft_strchr(ft_strchr(s, ',') + 1, ',') + 1, ','))
			exit_with_err(NULL, PARSE);
		else if (ft_strchr(ft_strchr(s, ',') + 1, ','))
			return ;
	}
	else
		exit_with_err(NULL, PARSE);
}

int	extract_color(t_player *plyr, char *color)
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
		exit_with_err(NULL, PARSE);
	color_c = ft_atoi(plyr, ft_mstrtrim(plyr->v, *s, " ", TMP));
	color_c <<= 8;
	s++;
	color_c |= ft_atoi(plyr, ft_mstrtrim(plyr->v, *s, " ", TMP));
	color_c <<= 8;
	s++;
	color_c |= ft_atoi(plyr, ft_mstrtrim(plyr->v, *s, " ", TMP));
	return (color_c);
}

char	*get_file_path(t_player *plyr, char *path)
{
	char	*str;

	str = NULL;
	str = ft_mstrdup(plyr->v->collector, \
	ft_mstrtrim(plyr->v, path, " ", TMP), TMP);
	return (str);
}

int	get_map_indx(t_player *plyr, int fd, int i, char *s)
{
	s = get_next_line(fd);
	while (s)
	{
		if (ft_strnstr(s, "NO", 2))
			plyr->v->no_c = get_file_path(plyr, s + 2);
		else if (ft_strnstr(s, "SO", 2))
			plyr->v->so_c = get_file_path(plyr, s + 2);
		else if (ft_strnstr(s, "WE", 2))
			plyr->v->we_c = get_file_path(plyr, s + 2);
		else if (ft_strnstr(s, "EA", 2))
			plyr->v->ea_c = get_file_path(plyr, s + 2);
		else if (ft_strnstr(s, "F", 1))
			plyr->v->f_color = extract_color(plyr, \
			ft_mstrtrim(plyr->v, s + 1, " ", TMP));
		else if (ft_strnstr(s, "C", 1))
			plyr->v->c_color = extract_color(plyr, \
			ft_mstrtrim(plyr->v, s + 1, " ", TMP));
		else if (ft_strnstr(s, "1", ft_strlen(s)))
			return (free(s), i);
		free(s);
		s = NULL;
		s = get_next_line(fd);
		i++;
	}
	return (0);
}
