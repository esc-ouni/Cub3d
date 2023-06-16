#include "Cub.h"

t_data 	*cast_rays(t_player *player, t_data *p_img)
{
	t_vector direction;
	direction.x = 0;
	direction.y = 0;
	draw_ray(p_img, player, direction);
	return (p_img);
}