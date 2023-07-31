/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:23:31 by idouni            #+#    #+#             */
/*   Updated: 2023/07/31 20:11:31 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	*ft_mstrdup(t_collector **collector, const char *s1, t_flag flag)
{
	size_t	i;
	char	*s;

	i = 0;
	s = NULL;
	if (!s1)
		return (NULL);
	s = (char *)h_malloc(collector, sizeof(char) * \
	(ft_strlen(s1) + 1), s, flag);
	while (s1[i] != '\0')
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

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

void	init_1(t_player *plyr, int argc, char const *argv[])
{
	plyr->v->mlx = NULL;
	plyr->v->win = NULL;
	plyr->v->fix_img = NULL;
	plyr->v->m_fix_img = NULL;
	plyr->p = NULL;
	exit_with_err(plyr, NONE);
	plyr->v->map = parse_file(plyr, argc, argv);
	check_paths(plyr);
	plyr->v->mlx = mlx_init();
	get_elements(plyr);
	plyr->v->win = mlx_new_window(plyr->v->mlx, plyr->width, \
	plyr->height, "cub3D");
	if (!plyr->v->mlx || !plyr->v->win)
		exit_with_err(NULL, MLX);
}

void	init_2(t_player *plyr)
{
	plyr->color = 0;
	plyr->last_pos = 0;
	plyr->b_p = 0;
	plyr->v->fix_img = draw_cf(plyr);
	plyr->v->m_fix_img = draw_2d_map(plyr);
	plyr->factor = BLOCK / M_B;
	plyr->m = 0;
	plyr->f_angle = (60.0 / plyr->width);
	plyr->mv_sp = (BLOCK / 7);
	plyr->yf = (BLOCK / 4);
	plyr->xf = (BLOCK / 4);
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
	t_vars				*vars;
	t_player			*plyr;

	collector = NULL;
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
	vars->c_color = 0;
	vars->f_color = 0;
	plyr->v = vars;
	init_1(plyr, argc, argv);
	init_2(plyr);
	return (plyr);
}
