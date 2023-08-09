/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:23:31 by idouni            #+#    #+#             */
/*   Updated: 2023/08/06 09:05:23 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	count_alloc_size(t_player *plyr, char const *argv[], int fd)
{
	int		size;
	char	*s;

	size = 0;
	s = NULL;
	(void)plyr;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit_with_err(NULL, OPEN);
	s = get_next_line(fd);
	while (s)
	{
		free(s);
		s = NULL;
		s = get_next_line(fd);
		size++;
	}
	close(fd);
	return (size += 1);
}

void	check_size(t_player *plyr)
{
	int		i;

	i = 0;
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
		exit_with_err(NULL, MAP);
}

void	init_1(t_player *plyr, int argc, char const *argv[])
{
	plyr->v->mlx = NULL;
	plyr->v->win = NULL;
	plyr->v->fix_img = NULL;
	plyr->v->m_fix_img = NULL;
	plyr->p = NULL;
	plyr->block = 1000;
	exit_with_err(plyr, NONE);
	plyr->v->map = parse_file(plyr, argc, argv);
	check_size(plyr);
	check_paths(plyr);
	plyr->v->mlx = mlx_init();
	if (!plyr->v->mlx)
		exit_with_err(NULL, MLX);
	plyr->v->win = mlx_new_window(plyr->v->mlx, plyr->width, \
	plyr->height, "cub3D");
	if (!plyr->v->win)
		exit_with_err(NULL, MLX);
	get_elements(plyr);
}

void	init_2(t_player *plyr)
{
	plyr->color = 0;
	plyr->last_pos = 0;
	plyr->b_p = 0;
	plyr->v->fix_img = draw_cf(plyr);
	plyr->v->m_fix_img = draw_2d_map(plyr);
	plyr->factor = plyr->block / M_B;
	plyr->m = 0;
	plyr->f_angle = (60.0 / plyr->width);
	plyr->mv_sp = (plyr->block / 7);
	plyr->yf = (plyr->block / 4);
	plyr->xf = (plyr->block / 4);
	plyr->p = h_malloc(plyr->v->collector, 3 * sizeof(void *), plyr->p, NTMP);
	plyr->p[0] = NULL;
	plyr->t_img = NULL;
	plyr->v2 = NULL;
	plyr->v2 = h_malloc(plyr->v->collector, sizeof(t_vector), plyr->v2, NTMP);
	plyr->v1 = NULL;
	plyr->v1 = h_malloc(plyr->v->collector, sizeof(t_vector), plyr->v1, NTMP);
	plyr->ray = NULL;
	plyr->ray = h_malloc(plyr->v->collector, (sizeof(t_ray) * \
	plyr->width) + 1, plyr->ray, NTMP);
}

t_player	*init(int argc, char const *argv[])
{
	static t_collector	*collector;
	t_player			*plyr;
	t_vars				*vars;

	plyr = NULL;
	vars = NULL;
	plyr = h_malloc(&collector, sizeof(t_player), vars, NTMP);
	resizer(plyr);
	vars = NULL;
	vars = h_malloc(&collector, sizeof(t_vars), vars, NTMP);
	vars->collector = &collector;
	vars->we_c = NULL;
	vars->no_c = NULL;
	vars->so_c = NULL;
	vars->ea_c = NULL;
	vars->we = NULL;
	vars->no = NULL;
	vars->so = NULL;
	vars->ea = NULL;
	vars->c_color = 0;
	vars->f_color = 0;
	plyr->v = vars;
	init_1(plyr, argc, argv);
	init_2(plyr);
	return (plyr);
}
