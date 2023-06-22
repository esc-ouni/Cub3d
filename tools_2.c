#include "Cub.h"

//######################

int darkenColor(int color, int amount) {
    int red = (color >> 16) & 0xFF;
    int green = (color >> 8) & 0xFF;
    int blue = color & 0xFF;

    red = (red * (100 - amount)) / 100;
    green = (green * (100 - amount)) / 100;
    blue = (blue * (100 - amount)) / 100;

    return (red << 16) | (green << 8) | blue;
}

//######################

void    draw_3d_map(t_player *player, t_data *p_img, t_ray *ray)
{
    int     i;
    int     start;
    int     end;
    float   w_height;
    int color = GREEN;

    i = 0;
    while (i < 320)
    {
        color = GREEN;
        w_height = ((140 / (ray[i].length * cos(ray[i].angle - player->angle))) * ((320/2)/tan(deg_to_rad(30))));

        start = (HEIGHT/2) - ((w_height)/2);
        end = (HEIGHT/2) - ((w_height)/2) + (w_height);
        if (end > 700 || start < 0)
        {
            start = 0;
            end = 700;
        }
        color = darkenColor(color, 4000/w_height);
        drawk_line(player, p_img, color, 1800 + i, (int)start, 1800 + i, (int)end);
        i++;
    }
}

void update_scene(t_player *player)
{
	t_data *p_img;
	t_ray  *ray;

	ray = NULL;
	ray = h_malloc(player->vars->collector, (sizeof(t_ray) * 320) + 1, ray, TMP);
	p_img = draw_2d_map(player);
	draw_player(player, p_img);
	ray = cast_rays(player, p_img, ray);
	draw_3d_map(player, p_img, ray);
	mlx_clear_window(player->vars->mlx, player->vars->win);
	mlx_put_image_to_window(player->vars->mlx, player->vars->win, p_img->img_ptr, 0, 0);
    if (player->vars->last_img)
	    mlx_destroy_image(player->vars->mlx, p_img->img_ptr);
	player->vars->last_img = NULL;
}

float   draw_ray(t_player *player, t_data *p_img, int color, t_ray ray)
{
    t_vector    *vec1;
    t_vector    *vec2;
    int         v_x;
    int         v_y;
    int         h_x;
    int         h_y;

    vec1 = find_horizontal_iterset(player, &ray);
    vec2 = find_vertical_iterset(player, &ray);
    
    v_x = ft_abs(player->p_x - vec1->x);
    v_y = ft_abs(player->p_y - vec1->y);
    
    h_x = ft_abs(player->p_x - vec2->x);
    h_y = ft_abs(player->p_y - vec2->y);
    if ((v_x < h_x) || (v_y < h_y))
    {
        draw_line(player, p_img, color, (int)vec1->x, (int)vec1->y);
        return (sqrt((ft_pow(vec1->x - player->p_x) + ft_pow(vec1->y - player->p_y))));
    }
    else
    {
        draw_line(player, p_img, color, (int)vec2->x, (int)vec2->y);
        return (sqrt((ft_pow(vec2->x - player->p_x) + ft_pow(vec2->y - player->p_y))));
    }
    return (10000);
}

t_ray *cast_rays(t_player *player, t_data *p_img, t_ray *ray)
{
    float angle = player->angle - deg_to_rad(30);
	int i = 0;

    while (i < 320)
    {
        ray[i].p_x = player->p_x;
        ray[i].p_y = player->p_y;
        ray[i].angle = up_degree(angle, 0.1875);
        angle = up_degree(angle, 0.1875);
        ray[i].length = draw_ray(player, p_img, BLUE, ray[i]);
        i++;
    }
    return (&(ray[0]));
}

int wall_hit_hup(t_player *player, int x, int y)
{
	int m_y = ((y)/BLOCK) - 1;
	int m_x = ((x)/BLOCK);

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

	if (m_x < 0|| m_y < 0)
		return 0;
	if (m_x > 35|| m_y > 13)
		return 0;
	if (player->vars->map[m_y][m_x] == '0')
		return (1);
	return (0);
}

t_vector *find_horizontal_iterset(t_player *player, t_ray *ray)
{
	t_vector *vector;
    int i = 0;
    float    stepy;
    float    stepx;

	vector = NULL;
	vector = h_malloc(player->vars->collector, sizeof(t_vector), vector, TMP);
    if ((ray->angle > 0 && ray->angle < M_PI))
    {
        stepy = BLOCK;
        stepx = (stepy / tan(ray->angle));
        vector->y = (ceil(player->p_y / BLOCK) * BLOCK);
        vector->x = player->p_x + ((vector->y - player->p_y) / tan(ray->angle));
        while (i < 36)
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
        while (i < 36)
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

t_vector *find_vertical_iterset(t_player *player, t_ray *ray)
{
	t_vector *vector;
    int i = 0;
    float    stepx;
    float    stepy;

	vector = NULL;
	vector = h_malloc(player->vars->collector, sizeof(t_vector), vector, TMP);
    if (((ray->angle > (3 * (M_PI / 2))) && (ray->angle < 2 * (M_PI))) || (((ray->angle > 0) && (ray->angle < (M_PI / 2)))))
    {
        stepx = BLOCK;
        stepy = stepx * tan(ray->angle);
        vector->x = (ceil(ray->p_x/ BLOCK) * BLOCK);
        vector->y = ray->p_y + ((vector->x - ray->p_x) * tan(ray->angle));
        while (i < 36)
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
        while (i < 36)
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
