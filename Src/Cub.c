/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:54:21 by idouni            #+#    #+#             */
/*   Updated: 2023/07/24 18:43:52 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	main(int argc, char const *argv[])
{
	t_player	*plyr;

	plyr = init(argc, argv);
	update_scene(plyr);
	mlx_loop_hook(plyr->v->mlx, hokking, plyr);
	mlx_loop(plyr->v->mlx);
	return (0);
}
