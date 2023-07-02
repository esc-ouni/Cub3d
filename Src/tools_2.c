#include "Cub.h"

// Global variables
int frameCount = 0;
int lastFrameTime = 0;

// Function to update and render the scene
void updateAndRenderScene(t_player *player)
{
    // Put your scene update and rendering logic here
	update_scene(player);
    
    // Increment frame count
    frameCount++;

    // Get the current time in milliseconds
    int currentTime = (int) (clock() * 1000 / CLOCKS_PER_SEC);

    // Calculate time difference from the last frame
    int deltaTime = currentTime - lastFrameTime;

    // Update the title of the window with the current FPS
    char fpsString[20];
    // printf("")
    sprintf(fpsString, "FPS: %.2f", 1000.0 / deltaTime);
    mlx_string_put(player->vars->mlx, player->vars->win, 1600, 10, 0x000000, fpsString);
    // printf("")

    // Update the last frame time
    lastFrameTime = currentTime;
}

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
    float   c;
    int     color;
    float   d_h = HEIGHT/2;

    c = ray[i].c;
    i = 0;
    while (i < WIDTH)
    {
        if (ray[i].side == HORZ_D)
            color = HORZ_D;
        else if (ray[i].side == HORZ_U)
            color = HORZ_U;
        else if (ray[i].side == VERT_L)
            color = VERT_L;
        else if (ray[i].side == VERT_R)
            color = VERT_R;
        w_height = c / (ray[i].length * trigo(ray[i].angle - player->angle, COS));
        start = d_h - (w_height/2);
        end = start + w_height;
        draw_wall_part(player, p_img, color, i, (int)start, i, (int)end, ray[i].tex_i, 5000/w_height);
        i++;
    }
}

t_data *ft_transparency(t_player *player, t_data *p_img, int width, int height)
{
    int i = 0, j = 0;
    while (i < WIDTH)
    {
        while (j < HEIGHT)
        {
            my_mlx_pixel_put(player, p_img, i, j, TRANS);
            j++;
        }
        i++;
        j = 0;
    }
    return (p_img);
}

void update_scene(t_player *player)
{
	t_data *p_img;
	t_ray  *ray;

	ray = NULL;
	ray = h_malloc(player->vars->collector, (sizeof(t_ray) * WIDTH) + 1, ray, TMP);
    p_img = new_image(player->vars);
    p_img = ft_transparency(player, p_img, WIDTH, HEIGHT);
	draw_player(player, p_img);
	ray = cast_rays(player, p_img, ray);


	draw_3d_map(player, p_img, ray);
	mlx_clear_window(player->vars->mlx, player->vars->win);
	mlx_put_image_to_window(player->vars->mlx, player->vars->win, player->vars->fix_img->img_ptr, 0, 0);
	mlx_put_image_to_window(player->vars->mlx, player->vars->win, p_img->img_ptr, 0, 0);
	mlx_put_image_to_window(player->vars->mlx, player->vars->win, player->vars->m_fix_img->img_ptr, 0, 0);
    // if (player->vars->last_img)
	//     mlx_destroy_image(player->vars->mlx, p_img->img_ptr);
	// player->vars->last_img = NULL;
}


float   draw_ray(t_player *player, t_data *p_img, int color, t_ray *ray)
{
    int         v_x;
    int         v_y;
    int         h_x;
    int         h_y;


    vec1 = find_vertical_iterset(player, ray, vec1);
    vec2 = find_horizontal_iterset(player, ray, vec2);
    
    v_x = ft_abs(player->p_x - vec1->x);
    // v_y = ft_abs(player->p_y - vec1->y);
    
    h_x = ft_abs(player->p_x - vec2->x);
    // h_y = ft_abs(player->p_y - vec2->y);
    if ((v_x < h_x))
    {
        // draw_line(player, p_img, color, (int)vec1->x, (int)vec1->y);
        if (ray->angle > M_PI / 2 && ray->angle < 3 * M_PI / 2)
            ray->side = VERT_L;
        else
            ray->side = VERT_R;
        ray->tex_i = (int)vec1->y % BLOCK;
        ray->length = sqrt((ft_pow(vec1->x - player->p_x) + ft_pow(vec1->y - player->p_y)));
        return (0);
    }
    else
    {
        // draw_line(player, p_img, color, (int)vec2->x, (int)vec2->y);
        if (ray->angle > M_PI && ray->angle < 2 * M_PI)
            ray->side = HORZ_U;
        else
            ray->side = HORZ_D;
        ray->tex_i = (int)vec2->x % BLOCK;
        ray->length = sqrt((ft_pow(vec2->x - player->p_x) + ft_pow(vec2->y - player->p_y)));
        return (0);
    }
    ray->length = 0;
    return (0);
}

t_ray *cast_rays(t_player *player, t_data *p_img, t_ray *ray)
{
    float angle = player->angle - deg_to_rad(30);
	int i = 0;

    float c = ((700 * 50) / trigo(deg_to_rad(30), TAN));
    while (i < WIDTH    )
    {
        angle = up_degree(angle, (60.0/WIDTH));
        ray[i].p_x = player->p_x;
        ray[i].p_y = player->p_y;
        ray[i].angle = angle;
        ray[i].t1 = trigo(ray[i].angle, TAN);
        ray[i].t2 = trigo((2 * M_PI) - ray[i].angle, TAN);
        ray[i].c = c;
        draw_ray(player, p_img, RED, &ray[i]);
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




// t_vector *find_horizontal_iterset(t_player *player, t_ray *ray)
// {
// 	t_vector *vector;
//     int i = 0;
//     float    stepy;
//     float    stepx;

// 	vector = NULL;
// 	vector = h_malloc(player->vars->collector, sizeof(t_vector), vector, TMP);
//     if ((ray->angle > 0 && ray->angle < M_PI))
//     {
//         stepy = BLOCK;
//         stepx = (stepy / ray->t1);
//         vector->y = (ceil(player->p_y / BLOCK) * BLOCK);
//         vector->x = player->p_x + ((vector->y - player->p_y) / ray->t1);
//         while (i < 36)
//         {
//             if (!wall_hit_hdn(player, (int)vector->x, (int)vector->y))
//                 return (vector);
//             vector->y += stepy;
//             vector->x += stepx;
//             i++;
//         }
//         return (vector);
//     }
//     else if (ray->angle > M_PI && ray->angle < 2 * M_PI)
//     {
//         stepy = -BLOCK;
//         stepx = (BLOCK / ray->t2);
//         vector->y = floor(player->p_y / BLOCK) * BLOCK ;
//         vector->x = player->p_x + (player->p_y - vector->y) / ray->t2;   
//         while (i < 36)
//         {
//             if (!wall_hit_hup(player, (int)vector->x, (int)vector->y))
//                 return (vector);
//             vector->x += stepx;
//             vector->y += stepy;
//             i++;
//         }
//         return (vector);
//     }
//     return (vector);
// }


t_vector *find_horizontal_iterset(t_player *player, t_ray *ray, t_vector *vector)
{
    float stepy, stepx;
    int i = 0;

    if ((ray->angle > 0 && ray->angle < M_PI))
    {
        stepy = BLOCK;
        stepx = (stepy / ray->t1);
        float ceil_p_y = ceil(player->p_y / BLOCK) * BLOCK;
        vector->y = ceil_p_y;
        vector->x = player->p_x + ((ceil_p_y - player->p_y) / ray->t1);
        while (i < 36)
        {
            if (!wall_hit_hdn(player, (int)vector->x, (int)vector->y))
                return vector;
            vector->y += stepy;
            vector->x += stepx;
            i++;
        }
        return vector;
    }
    else if (ray->angle > M_PI && ray->angle < 2 * M_PI)
    {
        stepy = -BLOCK;
        stepx = (BLOCK / ray->t2);
        float floor_p_y = floor(player->p_y / BLOCK) * BLOCK;
        vector->y = floor_p_y;
        vector->x = player->p_x + (player->p_y - floor_p_y) / ray->t2;
        while (i < 36)
        {
            if (!wall_hit_hup(player, (int)vector->x, (int)vector->y))
                return vector;
            vector->x += stepx;
            vector->y += stepy;
            i++;
        }
        return vector;
    }
    return vector;
}






t_vector *find_vertical_iterset(t_player *player, t_ray *ray, t_vector *vector)
{
    int i = 0;
    float    stepx;
    float    stepy;

    if (((ray->angle > (3 * (M_PI / 2))) && (ray->angle < 2 * (M_PI))) || (((ray->angle > 0) && (ray->angle < (M_PI / 2)))))
    {
        stepx = BLOCK;
        stepy = stepx * ray->t1;
        vector->x = (ceil(ray->p_x/ BLOCK) * BLOCK);
        vector->y = ray->p_y + ((vector->x - ray->p_x) * ray->t1);
        while (i < 36)
        {
            if (!wall_hit_vrg(player, (int)vector->x, (int)vector->y))
                return (vector);
            vector->x += stepx;
            vector->y += stepy;
            i++;
        }
        return NULL;
    }
    else if ((ray->angle > (M_PI / 2)) || (ray->angle < 3 * (M_PI / 2)))
    {
        stepx = -BLOCK;
        stepy = BLOCK * ray->t2;
        vector->x = (floor(ray->p_x / BLOCK) * BLOCK);
        vector->y = ray->p_y - ((vector->x - ray->p_x) * ray->t2);
        while (i < 36)
        {
            if (!wall_hit_vlf(player, (int)vector->x, (int)vector->y))
                return (vector);
            vector->x += stepx;
            vector->y += stepy;
            i++;
        }
        return (vector);
    }
    return (vector);
}
