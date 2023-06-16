#include "Cub.h"

void draw_ray(t_player *player, t_data *p_img, int color)
{
    int x1 = (int)player->p_x;
    int y1 = (int)player->p_y;
    int x2 = (int)(player->p_x + player->direction->x * 150);
    int y2 = (int)(player->p_y + player->direction->y * 150);

    float dx = x2 - x1;
    float dy = y2 - y1;
    float steps = fabs(dy);
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
    float x_inc = dx / steps;
    float y_inc = dy / steps;

    float x = x1;
    float y = y1;

    for (int i = 0; i < steps; i++)
    {
		my_mlx_pixel_put(p_img, (int)x, (int)y, color);
        x += x_inc;
        y += y_inc;
    }
}

t_data 	*cast_rays(t_player *player, t_data *p_img)
{
	int k = 0;
	float tmpx;
	float tmpy;


	tmpx = player->direction->x;
	tmpy = player->direction->y;

    draw_ray(player, p_img, RED);
    rotate_vector(player->direction, -30);
    while (k < 600)
    {
        rotate_vector(player->direction, 0.1);
        draw_ray(player, p_img, BLUE);
        k++;
    }
	player->direction->x = tmpx;
	player->direction->y = tmpy;
	return (p_img);
}

t_vector *find_horizontal_iterset(t_player *player)
{
	t_vector *vector;

	vector = NULL;
	vector = h_malloc(player->vars->collector, sizeof(t_vector), vector, NTMP);
	vector->y = (int)player->p_y;
	vector->x = (int)player->p_y;
}