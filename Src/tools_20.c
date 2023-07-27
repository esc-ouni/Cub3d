/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_20.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:23:31 by idouni            #+#    #+#             */
/*   Updated: 2023/07/27 23:46:45 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	check_existence(t_player *plyr, char *file_dstination)
{
	int	fd;

	fd = 0;
	fd = open(file_dstination, O_RDONLY);
	if (fd == -1)
		exit_with_err(plyr, PARSE);
	close(fd);
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
