/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:54:21 by idouni            #+#    #+#             */
/*   Updated: 2023/07/27 10:33:08 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	leak()
{
	system("leaks cub3D");
}
int	main(int argc, char const *argv[])
{
	// atexit(leak);
	t_player	*plyr;

	plyr = init(argc, argv);
	update_scene(plyr);
	mlx_loop_hook(plyr->v->mlx, hokking, plyr);
	mlx_loop(plyr->v->mlx);
	return (0);
}
