/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:54:44 by idouni            #+#    #+#             */
/*   Updated: 2023/07/24 10:43:19 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

void	exit_with_err(t_collector **collector, t_flag cause)
{
	if (cause == MALLOC)
		write (2, "\033[0;32mError\nMALLOC_FAILED\033[0;37m\n", 35);
	else if (cause == PARSE)
		write (2, "\033[0;32mError\nMISCONFIGURATION_OF_.cub_FILE\033[0;37m\n", 51);
	else if (cause == ARGS)
		write (2, "\033[0;32mError\nNOT_A_VALID_ARGS_NUMBER\033[0;37m\n", 45);
	else if (cause == MLX)
		write (2, "\033[0;32mError\nMLX_FAILED\033[0;37m\n", 32);
	else if (cause == OPEN)
		write (2, "\033[0;32mError\nUNABLE_TO_OPEN_A_FILE\033[0;37m\n", 43);
	else if (cause == MAP)
		write (2, "\033[0;32mError\nINCOMPATIBLE_SIZE\033[0;37m\n", 39);
	ft_collectorclear(collector, ALL);
	exit (1);
}

void duppp(t_player *plyr, int fd, t_varr *varr, char *str)
{
	while ((str = get_next_line(fd)))
	{
		varr->fp = ft_msplit(plyr->v, str, ' ', TMP)[0];
		if (varr->fp && !ft_strncmp(varr->fp, "NO", ft_strlen(varr->fp)))
			(varr->n)++;
		else if (varr->fp && !ft_strncmp(varr->fp, "SO", ft_strlen(varr->fp)))
			(varr->s)++;
		else if (varr->fp && !ft_strncmp(varr->fp, "WE", ft_strlen(varr->fp)))
			(varr->w)++;
		else if (varr->fp && !ft_strncmp(varr->fp, "EA", ft_strlen(varr->fp)))
			(varr->e)++;
		else if (varr->fp && !ft_strncmp(varr->fp, "F", ft_strlen(varr->fp)))
			(varr->f)++;
		else if (varr->fp && !ft_strncmp(varr->fp, "C", ft_strlen(varr->fp)))
			(varr->c)++;
		else if (varr->fp && !ft_strnstr(str, "1", ft_strlen(str)) && \
		!ft_strnstr(str, "0", ft_strlen(str)))
			(varr->k)++;
		free(str);
	}
	if (varr->k)
		exit_with_err(plyr->v->collector, PARSE);
}

void    check_dups(t_player *plyr, char const *argv[])
{
	t_varr	*varr;
	char	*str;
	int		fd;

	str = NULL;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit_with_err(plyr->v->collector, OPEN);
	varr = NULL;
	varr = h_malloc(plyr->v->collector, sizeof(t_varr), varr, TMP);
	varr->c = 0;
	varr->f = 0;
	varr->n = 0;
	varr->s = 0;
	varr->e = 0;
	varr->w = 0;
	varr->k = 0;
	varr->fp = NULL;
	duppp(plyr, fd, varr, str);
	if (varr->n != 1 || varr->e != 1 || varr->w != 1 \
	|| varr->s != 1 || varr->f != 1 || varr->c != 1)
		exit_with_err(plyr->v->collector, PARSE);
}

void	check_errs(t_player *plyr, char const *argv[])
{
	if (ft_strlen(strstr(argv[1], ".cub")) != 4)
		exit_with_err(plyr->v->collector, PARSE);
}

int	point_surronded(t_player *plyr, char **map, int y, int x)
{
	int	x_m;
	int	y_m;

	x_m = 0;
	y_m = 0;
	while (map[y_m])
		y_m++;

	x_m = ft_strlen(map[y]);
	if ((x - 1) < 0 || (x + 1) > x_m)
		exit_with_err(plyr->v->collector, PARSE);
	if (map[y][x-1] == ' ' || map[y][x+1] == ' ')
		exit_with_err(plyr->v->collector, PARSE);
	if ((y - 1) < 0 || (y + 1) > y_m)
		exit_with_err(plyr->v->collector, PARSE);
	if (x >= ft_strlen(map[y-1]) || x >= ft_strlen(map[y+1]))
		exit_with_err(plyr->v->collector, PARSE);
	if (map[y-1][x] == ' ' || map[y+1][x] == ' ')
		exit_with_err(plyr->v->collector, PARSE);
	return (1);
}

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
			if (map[y][x] == 'N' || map[y][x] == 'E' || map[y][x] == 'W' || map[y][x] == 'S')
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

	check_mapb_t(plyr, map, &chr, &c);
	if (c != 1)
		exit_with_err(plyr->v->collector, PARSE);
	if (chr == 'N')
		plyr->angle = 3 * (M_PI/2);
	else if (chr == 'E')
		plyr->angle = 0;
	else if (chr == 'S')
		plyr->angle = M_PI/2;
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
			else if ((map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E' || map[y][x] == 'W'))
				point_surronded(plyr, map, y, x);
			x++;
		}
		y++;
		x = 0;
	}
}

char	**get_map_cont(t_player *plyr, int fd, int t, char **map)
{
	int		itsmap;
	int		i2;
	int		i;
	char	*s;

	i = 0;
	i2 = 0;
	s = NULL;
	itsmap = 0;
	while ((s = get_next_line(fd)))
	{
		if (i == t)
			itsmap = 1;
		if (itsmap)
		{
			map[i2] = ft_mstrdup(plyr->v->collector, s, NTMP);
			i2++;
		}
		free(s);
		s = NULL;
		i++;
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
			plyr->v->up_c = ft_mstrdup(plyr->v->collector, ft_mstrtrim(plyr->v, s+2, " ", TMP), TMP);
		else if (ft_strnstr(s, "SO", 2))
			plyr->v->dn_c = ft_mstrdup(plyr->v->collector, ft_mstrtrim(plyr->v, s+2, " ", TMP), TMP);
		else if (ft_strnstr(s, "WE", 2))
			plyr->v->rg_c = ft_mstrdup(plyr->v->collector, ft_mstrtrim(plyr->v, s+2, " ", TMP), TMP);
		else if (ft_strnstr(s, "EA", 2))
			plyr->v->lf_c = ft_mstrdup(plyr->v->collector, ft_mstrtrim(plyr->v, s+2, " ", TMP), TMP);
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

void    check_xpm_size(t_player *plyr, char *file_dstination)
{
	char	**sp;
	char	*s;
	int		fd;

	sp = NULL;
	s = NULL;
	fd = 0;
	fd = open(file_dstination, O_RDONLY);
	if (fd == -1)
		exit_with_err(plyr->v->collector, OPEN);
	while ((s = get_next_line(fd)))
	{
		if (ft_strnstr(s, "\"", 1))
		{
			sp = ft_msplit(plyr->v, s+1, ' ', TMP);
			free(s);
			break ;
		}
		free(s);
		s = NULL;
	}
	if (!strcmp(sp[0], "1000") && !strcmp(sp[1], "1000"))
		return ;
	else
		exit_with_err(plyr->v->collector, MAP);
}

int	get_elements(t_player *plyr, char const *argv[])
{
	int	i;

	i = 0;
	i = get_elem(plyr, argv);
	plyr->v->up = new_image_from_xpm(plyr, plyr->v->up_c);
	check_xpm_size(plyr, plyr->v->up_c);
	plyr->v->dn = new_image_from_xpm(plyr, plyr->v->dn_c);
	check_xpm_size(plyr, plyr->v->dn_c);
	plyr->v->lf = new_image_from_xpm(plyr, plyr->v->lf_c);
	check_xpm_size(plyr, plyr->v->lf_c);
	plyr->v->rg = new_image_from_xpm(plyr, plyr->v->rg_c);
	check_xpm_size(plyr, plyr->v->rg_c);
	return (i);
}

char **parse_file(t_player *plyr, int argc, char const *argv[])
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

float    trigo(float  angle, t_flag flag)
{
	// static int i;

	// printf("angle : %f, index : %d\n",rad_to_deg(angle) ,i++);
	if (flag == COS)
	{
		// printf("COS\n");
		return (cos(angle));
	}
	else if (flag == SIN)
	{
		// printf("SIN\n");
		return (sin(angle));
	}
	else if (flag == TAN)
	{
		// printf("TAN\n");
		return (tan(angle));
	}
	return(0);
}
