/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_20.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:23:31 by msamhaou          #+#    #+#             */
/*   Updated: 2023/07/28 01:13:55 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	destruct(t_player *r_p)
{
	destroy_prev_imges(r_p);
	destroy_fix_imges(r_p);
	ft_collectorclear(r_p->v->collector, ALL);
}

void	check_existence(t_player *plyr, char *file_dstination)
{
	int	fd;

	fd = 0;
	(void)plyr;
	fd = open(file_dstination, O_RDONLY);
	if (fd == -1)
		exit_with_err(NULL, PARSE);
	close(fd);
}

int	m_hookp(int keycode, int x, int y, t_player *plyr)
{
	(void)y;
	if (keycode == 1)
	{
		plyr->b_p = 1;
		plyr->last_pos = x;
	}
	return (0);
}

int	m_hookr(int keycode, int x, int y, t_player *plyr)
{
	(void)x;
	(void)y;
	if (keycode == 1)
		plyr->b_p = 0;
	return (0);
}

void	get_elements(t_player *plyr)
{
	plyr->v->no = new_image_from_xpm(plyr, plyr->v->no_c);
	check_xpm_size(plyr, plyr->v->no_c);
	plyr->v->we = new_image_from_xpm(plyr, plyr->v->we_c);
	check_xpm_size(plyr, plyr->v->we_c);
	plyr->v->so = new_image_from_xpm(plyr, plyr->v->so_c);
	check_xpm_size(plyr, plyr->v->so_c);
	plyr->v->ea = new_image_from_xpm(plyr, plyr->v->ea_c);
	check_xpm_size(plyr, plyr->v->ea_c);
}
