#include "Cub.h"

void update_scene(t_player *player)
{
	t_data *p_img;
	t_ray  *ray;

	ray = NULL;
	ray = h_malloc(player->vars->collector, (sizeof(t_ray) * WIDTH) + 1, ray, NTMP);
	p_img = draw_2d_map(player);
	draw_player(player, p_img);
	cast_rays(player, p_img, ray);
	mlx_clear_window(player->vars->mlx, player->vars->win);
	mlx_put_image_to_window(player->vars->mlx, player->vars->win, p_img->img_ptr, 0, 0);
	// p_img = draw_3d_map(player, p_img, ray);

}

float   draw_ray(t_player *player, t_data *p_img, int color, t_ray ray)
{
    t_vector    *vec1;
    t_vector    *vec2;
    int         v_x;
    int         v_y;
    int         h_x;
    int         h_y;

    vec1 = find_horizontal_iterset(player, &ray, color);
    vec2 = find_vertical_iterset(player, &ray, color);
    
    v_x = fabs(player->p_x - vec1->x);
    v_y = fabs(player->p_y - vec1->y);
    h_x = fabs(player->p_x - vec2->x);
    h_y = fabs(player->p_y - vec2->y);
    if ( v_x < h_x || v_y < h_y)
    {
        draw_line(player, p_img, color, (int)vec1->x, (int)vec1->y);
        return (sqrt((ft_pow(v_x) + ft_pow(v_y))));
    }
    else
    {
        draw_line(player, p_img, color, (int)vec2->x, (int)vec2->y);
        return (sqrt((ft_pow(h_x) + ft_pow(h_y))));
    }
    return (10000);
}

t_ray *cast_rays(t_player *player, t_data *p_img, t_ray *ray)
{
    float angle = player->angle - deg_to_rad(30);
	int i = 0;

    while (i < 360)
    {
        ray[i].p_x = player->p_x;
        ray[i].p_y = player->p_y;
        ray[i].angle = up_degree(angle, 0.16);
        angle = up_degree(angle, 0.16);
        ray[i].length = draw_ray(player, p_img, BLUE, ray[i]);
        i++;
    }
    // ray[i] = NULL;
    return (&(ray[0]));
}

int wall_hit_hup(t_player *player, int x, int y)
{
	int m_y = ((y)/BLOCK) - 1;
	int m_x = ((x)/BLOCK);

    // printf("p_x : %d, p_y : %d\n",m_x , m_y);
	if (m_x < 0|| m_y < 0)
		return 0;
	if (m_x > 35|| m_y > 13)
		return 0;
	if (player->vars->map[m_y][m_x] == '0')
		return (1);
	return (0);
}

int wall_hit_hdn(t_player *player, int x, int y)
{
	int m_y = ((y)/BLOCK);
	int m_x = ((x)/BLOCK);

    // printf("p_x : %d, p_y : %d\n",m_x , m_y);
	if (m_x < 0|| m_y < 0)
		return 0;
	if (m_x > 35|| m_y > 13)
		return 0;
	if (player->vars->map[m_y][m_x] == '0')
		return (1);
	return (0);
}

int wall_hit_vrg(t_player *player, int x, int y)
{
	int m_y = ((y)/BLOCK);
	int m_x = ((x)/BLOCK);

    // printf("p_x : %d, p_y : %d\n",m_x , m_y);
	if (m_x < 0|| m_y < 0)
		return 0;
	if (m_x > 35|| m_y > 13)
		return 0;
	if (player->vars->map[m_y][m_x] == '0')
		return (1);
	return (0);
}

int wall_hit_vlf(t_player *player, int x, int y)
{
	int m_y = ((y)/BLOCK);
	int m_x = ((x)/BLOCK) - 1;

    // printf("p_x : %d, p_y : %d\n",m_x , m_y);
	if (m_x < 0|| m_y < 0)
		return 0;
	if (m_x > 35|| m_y > 13)
		return 0;
	if (player->vars->map[m_y][m_x] == '0')
		return (1);
	return (0);
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
            if (!wall_hit_hdn(player, (int)vector->x, (int)vector->y))
            {
                return (vector);
            }
            vector->y += stepy;
            vector->x += stepx;
            i++;
        }
        return (vector);
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
            if (!wall_hit_hup(player, (int)vector->x, (int)vector->y))
            {
                return (vector);
            }
            vector->x += stepx;
            vector->y += stepy;
            i++;
        }
        return (vector);
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
            if (!wall_hit_vrg(player, (int)vector->x, (int)vector->y))
            {
                return (vector);
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
            if (!wall_hit_vlf(player, (int)vector->x, (int)vector->y))
            {
                return (vector);
            }
            vector->x += stepx;
            vector->y += stepy;
            i++;
        }
        return (vector);
    }
    return (vector);
}
