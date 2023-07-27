/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:54:44 by idouni            #+#    #+#             */
/*   Updated: 2023/07/27 23:00:24 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	exit_with_err(t_player *plyr, t_flag cause)
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
	if (plyr)
		ft_collectorclear(NULL, plyr, ALL);
	exit(0);
}

void	duppp(t_player *plyr, int fd, t_varr *varr, char *str)
{
	str = get_next_line(fd);
	while (str)
	{
		varr->fp = ft_msplit(plyr->v, str, ' ', TMP)[0];
		if (varr->fp && !ft_strcmp(varr->fp, "NO"))
			(varr->n)++;
		else if (varr->fp && !ft_strcmp(varr->fp, "SO"))
			(varr->s)++;
		else if (varr->fp && !ft_strcmp(varr->fp, "WE"))
			(varr->w)++;
		else if (varr->fp && !ft_strcmp(varr->fp, "EA"))
			(varr->e)++;
		else if (varr->fp && !ft_strcmp(varr->fp, "F"))
			(varr->f)++;
		else if (varr->fp && !ft_strcmp(varr->fp, "C"))
			(varr->c)++;
		else if (varr->fp && !ft_strnstr(str, "1", ft_strlen(str)))
			(varr->k)++;
		if (varr->k)
			exit_with_err(plyr, PARSE);
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
}

void	check_dups(t_player *plyr, char const *argv[])
{
	t_varr	*varr;
	char	*str;
	int		fd;

	str = NULL;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit_with_err(plyr, OPEN);
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
		exit_with_err(plyr, PARSE);
}

void	check_errs(t_player *plyr, char const *argv[])
{
	if (ft_strlen(ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]))) != 4)
		exit_with_err(plyr, PARSE);
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
		exit_with_err(plyr, PARSE);
	if (map[y][x - 1] == ' ' || map[y][x + 1] == ' ')
		exit_with_err(plyr, PARSE);
	if ((y - 1) < 0 || (y + 1) > y_m)
		exit_with_err(plyr, PARSE);
	if (x >= ft_strlen(map[y - 1]) || x >= ft_strlen(map[y + 1]))
		exit_with_err(plyr, PARSE);
	if (map[y - 1][x] == ' ' || map[y + 1][x] == ' ')
		exit_with_err(plyr, PARSE);
	return (1);
}
