/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_18.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:23:31 by idouni            #+#    #+#             */
/*   Updated: 2023/07/24 16:57:54 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

void	draw_point(t_player *plyr, int x, int y, int color)
{
	int	i;
	int	j;

	i = -2;
	j = -2; 
	while (i < 4)
	{
		while (i < 2)
		{
			while (j < 2)
			{
				my_mlx_pixel_put(plyr, x + i, y + j, color);
				j++;
			}
			i++;
			j = -2;
		}
		i++;
	}
}

float	ft_pow(float n)
{
	return (n * n);
}

float	ft_abs(float n)
{
	if (n < 0)
		n = -n;
	return (n);
}
