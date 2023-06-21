#include "Cub.h"

void update_scene(t_player *player)
{
	t_data *p_img;
	t_ray  *ray;

	ray = NULL;
	ray = h_malloc(player->vars->collector, (sizeof(t_ray) * WIDTH) + 1, ray, NTMP);
	p_img = draw_2d_map(player);
	draw_player(player, p_img);
	mlx_clear_window(player->vars->mlx, player->vars->win);
	mlx_put_image_to_window(player->vars->mlx, player->vars->win, p_img->img_ptr, 0, 0);
	cast_rays(player, p_img, ray);
	// p_img = draw_3d_map(player, p_img, ray);

}

t_ray   *draw_ray(t_player *player, t_data *p_img, int color, t_ray ray)
{
    ray.p_x = player->p_x;
    ray.p_y = player->p_y;
    // rotate_vector(ray.direction, ray.angle);
    // ray.angle = player->angle;
    printf("player->angle : %f, ray->angle : %f\n",player->angle, ray.angle);
    find_horizontal_iterset(player, &ray, color);
    find_vertical_iterset(player, &ray, color);
    printf("\n\n");
    return (&ray);
}

t_data 	*cast_rays(t_player *player, t_data *p_img, t_ray *ray)
{
    float angle = player->angle - deg_to_rad(30);
    int k = 0;
	int i = 0;

    ray[i].p_x = player->p_x;
    ray[i].p_y = player->p_y;
    ray[i].angle = player->angle;
    draw_ray(player, p_img, BLUE, ray[i]);
    i++;
        // ray[i].p_x = player->p_x;
        // ray[i].p_y = player->p_y;
        // ray[i].angle = up_degree(angle, 3);
        // draw_ray(player, p_img, RED, ray[i]);
    while (i < 20)
    {
        ray[i].p_x = player->p_x;
        ray[i].p_y = player->p_y;
        ray[i].angle = up_degree(angle, 3);
        angle = up_degree(angle, 3);
        draw_ray(player, p_img, RED, ray[i]);
        i++;
    }

	return (p_img);
}

t_vector *find_horizontal_iterset(t_player *player, t_ray *ray, int color)
{
	t_vector *vector;
    int i = 0;
    float    stepy;
    float    stepx;

	vector = NULL;
	vector = h_malloc(player->vars->collector, sizeof(t_vector), vector, NTMP);
    if ((ray->angle > 0 && ray->angle < M_PI))
    {
        stepy = BLOCK;
        stepx = (stepy / tan(ray->angle));
        vector->y = (ceil(player->p_y / BLOCK) * BLOCK);
        vector->x = player->p_x + ((vector->y - player->p_y) / tan(ray->angle));
        // printf("angle : %f, p_x : %f, p_y : %f\n",ray->angle , vector->x, vector->y);
        while (i < 50)
        {
            if (!check_collision_v2(player, (int)vector->x, (int)vector->y))
            {
                draw_line(player, NULL, color, (int)vector->x, (int)vector->y);
                return NULL;
            }
            vector->y += stepy;
            vector->x += stepx;
            i++;
        }
        return (NULL);
    }
    else if (ray->angle > M_PI && ray->angle < 2 * M_PI)
    {
        stepy = -BLOCK;
        stepx = (BLOCK / tan((2 * M_PI) - ray->angle));
        vector->y = floor(player->p_y / BLOCK) * BLOCK ;
        vector->x = player->p_x + (player->p_y - vector->y) / tan((2 * M_PI) - ray->angle);   
        // printf("angle : %f, p_x : %f, p_y : %f\n",ray->angle , vector->x, vector->y);
        while (i < 50)
        {
            if (!check_collision_v2(player, (int)vector->x, (int)vector->y))
            {
                draw_line(player, NULL, color, (int)vector->x, (int)vector->y);
                return NULL;
            }
            vector->x += stepx;
            vector->y += stepy;
            i++;
        }
        return (NULL);
    }
    return (vector);
}

t_vector *find_vertical_iterset(t_player *player, t_ray *ray, int color)
{
	t_vector *vector;
    int i = 0;
    float    stepx;
    float    stepy;

	vector = NULL;
	vector = h_malloc(player->vars->collector, sizeof(t_vector), vector, NTMP);
    if ((ray->angle > (3 * (M_PI / 2))) && (ray->angle < 2 * (M_PI)) || ((ray->angle > 0) && (ray->angle < (M_PI / 2))))
    {
        stepx = BLOCK;
        stepy = stepx * tan(ray->angle);
        vector->x = (ceil(ray->p_x/ BLOCK) * BLOCK);
        vector->y = ray->p_y + ((vector->x - ray->p_x) * tan(ray->angle));
        // printf("angle : %f, p_x : %f, p_y : %f\n",ray->angle , vector->x, vector->y);    
        while (i < 50)
        {
            if (!check_collision_v2(player, (int)vector->x, (int)vector->y))
            {
                draw_line(player, NULL, color, (int)vector->x, (int)vector->y);
                return NULL;
            }
            vector->x += stepx;
            vector->y += stepy;
            i++;
        }
        return NULL;
    }
    else if ((ray->angle > (M_PI / 2)) || (ray->angle < 3 * (M_PI / 2)))
    {
        stepx = -BLOCK;
        stepy = BLOCK * tan (2 * PI - ray->angle);
        vector->x = (floor(ray->p_x / BLOCK) * BLOCK);
        vector->y = ray->p_y - ((vector->x - ray->p_x) * tan (2 * M_PI - ray->angle));
        while (i < 50)
        {
            if (!check_collision_v2(player, (int)vector->x, (int)vector->y))
            {
                draw_line(player, NULL, color, (int)vector->x, (int)vector->y);
                return NULL;
            }
            vector->x += stepx;
            vector->y += stepy;
            i++;
        }
        return NULL;
    }
    return (vector);
}
