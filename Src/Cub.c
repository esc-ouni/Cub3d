/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:54:21 by idouni            #+#    #+#             */
/*   Updated: 2023/07/03 13:54:22 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

int main(int argc, char const *argv[])
{
	t_player 		*player;

	player = init(argc, argv);
	update_scene(player);
	hooks(player);
	return 0;
}
