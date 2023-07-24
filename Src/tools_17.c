/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_17.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:23:31 by idouni            #+#    #+#             */
/*   Updated: 2023/07/24 16:54:15 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

int	get_elem(t_player *plyr, char const *argv[])
{
	char	*s;
	int		fd;
	int		i;

	s = NULL;
	i = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit_with_err(plyr->v->collector, OPEN);
	i = get_map_indx(plyr, fd, i, s);
	return (i);
}

void	check_xpm_size2(t_player *plyr, int fd)
{
	char	*s;
	char	**sp;

	sp = NULL;
	s = NULL;
	s = get_next_line(fd);
	while (s)
	{
		if (ft_strnstr(s, "\"", 1))
		{
			sp = ft_msplit(plyr->v, s + 1, ' ', TMP);
			free(s);
			break ;
		}
		free(s);
		s = NULL;
		s = get_next_line(fd);
	}
	if (!ft_strcmp(sp[0], "1000") && !ft_strcmp(sp[1], "1000"))
		return ;
	else
		exit_with_err(plyr->v->collector, MAP);
}

void	check_xpm_size(t_player *plyr, char *file_dstination)
{
	int		fd;

	fd = 0;
	fd = open(file_dstination, O_RDONLY);
	if (fd == -1)
		exit_with_err(plyr->v->collector, OPEN);
	check_xpm_size2(plyr, fd);
}

int	get_elements(t_player *plyr, char const *argv[])
{
	int	i;

	i = 0;
	i = get_elem(plyr, argv);
	plyr->v->no = new_image_from_xpm(plyr, plyr->v->no_c);
	check_xpm_size(plyr, plyr->v->no_c);
	plyr->v->we = new_image_from_xpm(plyr, plyr->v->we_c);
	check_xpm_size(plyr, plyr->v->we_c);
	plyr->v->so = new_image_from_xpm(plyr, plyr->v->so_c);
	check_xpm_size(plyr, plyr->v->so_c);
	plyr->v->ea = new_image_from_xpm(plyr, plyr->v->ea_c);
	check_xpm_size(plyr, plyr->v->ea_c);
	return (i);
}

char	**parse_file(t_player *plyr, int argc, char const *argv[])
{
	char	**map;
	int		fd;
	int		i;

	i = 0;
	map = NULL;
	fd = 0;
	if (argc == 2 && argv[1])
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			exit_with_err(plyr->v->collector, OPEN);
		check_errs(plyr, argv);
		check_dups(plyr, argv);
		i = get_elements(plyr, argv);
		map = get_map(plyr, argv, i);
		check_map(plyr, map);
		return (map);
	}
	exit_with_err(plyr->v->collector, ARGS);
	return (NULL);
}
