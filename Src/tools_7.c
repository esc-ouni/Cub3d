/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:23:31 by idouni            #+#    #+#             */
/*   Updated: 2023/07/26 12:05:15 by idouni           ###   ########.fr       */
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
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit_with_err(plyr, OPEN);
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

void	init_2(t_player *plyr, int argc, char const *argv[])
{
	get_elements(plyr, argv);
	plyr->angle = 0;
	plyr->color = 0;
	plyr->v->fix_img = draw_cf(plyr);
	plyr->v->m_fix_img = draw_2d_map(plyr);
	plyr->factor = BLOCK / M_B;
	plyr->m = 0;
	plyr->f_angle = (60.0 / plyr->width);
	plyr->mv_sp = (BLOCK / 7);
	plyr->yf = (BLOCK / 4);
	plyr->xf = (BLOCK / 4);
	plyr->p = NULL;
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
	vars->mlx = NULL;
	vars->win = NULL;
	plyr->v->map = parse_file(plyr, argc, argv);
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, plyr->width, plyr->height, "Cub3D");
	if (!vars->mlx || !vars->win)
		exit_with_err(NULL, MLX);
	init_2(plyr, argc, argv);
	return (plyr);
}

int	hokking(t_player *plyr)
{
	mlx_hook(plyr->v->win, 17, 0, ft_ext, plyr);
	mlx_hook(plyr->v->win, 6, 0, mouse_movement, plyr);
	mlx_hook(plyr->v->win, 2, (1L << 0), handlerp, plyr);
	mlx_hook(plyr->v->win, 3, (1L << 1), handlerr, plyr);
	update_params(plyr);
	return (0);
}
