/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:54:21 by idouni            #+#    #+#             */
/*   Updated: 2023/07/29 21:17:53 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	leaks(void)
{
	system("leaks cub3D");
}

int	main(int argc, char const *argv[])
{
	t_player	*plyr;

	// atexit(leaks);
	plyr = init(argc, argv);
	update_scene(plyr);
	mlx_loop_hook(plyr->v->mlx, hokking, plyr);
	mlx_loop(plyr->v->mlx);
	return (0);
}
