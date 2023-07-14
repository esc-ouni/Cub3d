/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:54:41 by idouni            #+#    #+#             */
/*   Updated: 2023/07/14 10:20:04 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
    mlx_string_put(player->vars->mlx, player->vars->win, WIDTH - 150, 10, GREEN, fpsString);
    // printf("")

    // Update the last frame time
    lastFrameTime = currentTime;
}

//######################

int darkenColor(int color, int amount)
{
    (void)amount;
    int r = 0;
    int g = 0;
    int b = 0;

    b |= (unsigned char)color;
    color >>= 8;
    g |= (unsigned char)color;
    color >>= 8;
    r |= (unsigned char)color;
    b -= amount;
    r -= amount;
    g -= amount;
    if (b < 0)
        b = 0;
    if (r < 0)
        r = 0;
    if (g < 0)
        g = 0;
    color = 0;
    color |= r;
    color <<= 8;
    color |= g;
    color <<= 8;
    color |= b;
    return (color);
}

void draw_wall_S(t_player *player, t_data *p_img, t_ray ray, int x_index)
{
    int i = 0;
    int color;
    float w_heig = ((HEIGHT * 50) / trigo(deg_to_rad(30), TAN)) / (ray.length * trigo(ray.angle - player->angle, COS));
    int start = HEIGHT/2 - w_heig/2;
    color = 0;
    
    if (ray.side == HORZ_D || ray.side == HORZ_U)
        color = L_GREY;
    else if (ray.side == VERT_R || ray.side == VERT_L)
        color = GREY;
    color = darkenColor(color, ((int)ray.length * 255)/ 1700);
    while (i < w_heig)
    {
        if (start + i > 0 && start + i < HEIGHT)
            my_mlx_pixel_put(player, p_img, x_index, start + i, color);
        i++;
    }
}

void    draw_3d_map(t_player *player, t_data *p_img, t_ray *ray)
{
    int i = 0;
    (void)player;
    (void)p_img;
    (void)ray;

    while (i < WIDTH)
    {
        draw_wall_S(player, p_img, ray[i], i);
        i++;
    }
}

// void    draw_3d_map(t_player *player, t_data *p_img, t_ray *ray)
// {
//     int     i;
//     int     start;
//     float   w_height;
//     float   c;

//     c = ((900 * 50) / trigo(deg_to_rad(30), TAN));
//     i = 0;
//     while (i < WIDTH)
//     {
//         w_height = c / (ray[i].length * trigo(ray[i].angle - player->angle, COS));
//         start = HEIGHT/2 - (w_height/2);
//         draw_wall_part(player, p_img, ray[i], i, (int)start, i, start + w_height, ((int)ray[i].length * 255)/ 1600);
//         i++;
//     }
// }

t_data *ft_transparency(t_player *player, t_data *p_img, int width, int height)
{
    int i = 0;
    int j = 0;
    while (i < width)
    {
        while (j < height)
        {
            my_mlx_pixel_put(player, p_img, i, j, TRANS);
            j++;
        }
        i++;
        j = 0;
    }
    return (p_img);
}

void    destroy_fix_imges(t_player *player)
{
    mlx_destroy_image(player->vars->mlx, player->vars->dn->img_ptr);
    mlx_destroy_image(player->vars->mlx, player->vars->rg->img_ptr);
    mlx_destroy_image(player->vars->mlx, player->vars->lf->img_ptr);
    mlx_destroy_image(player->vars->mlx, player->vars->up->img_ptr);
    mlx_destroy_image(player->vars->mlx, player->vars->fix_img->img_ptr);
    mlx_destroy_image(player->vars->mlx, player->vars->m_fix_img->img_ptr);
}

void    destroy_prev_imges(t_player *player)
{
    int i = 0;

    while (player->p[i])
    {
        mlx_destroy_image(player->vars->mlx, player->p[i]);
        player->p[i] = NULL;
        i++;
    }   
}

void update_scene(t_player *player)
{
	t_data *p_img;
	t_data *p_r_img;

    destroy_prev_imges(player);
    p_img = new_image(player->vars, WIDTH, HEIGHT, TMP);
    p_r_img = new_image(player->vars, WIDTH, HEIGHT, TMP);
    p_img = ft_transparency(player, p_img, WIDTH, HEIGHT);
    p_r_img = ft_transparency(player, p_r_img, WIDTH, HEIGHT);
	draw_player(player, p_r_img);
	ray = cast_rays(player, p_r_img, ray);

	draw_3d_map(player, p_img, ray);//to_be_recoded
	mlx_clear_window(player->vars->mlx, player->vars->win);
	mlx_put_image_to_window(player->vars->mlx, player->vars->win, player->vars->fix_img->img_ptr, 0, 0);
	mlx_put_image_to_window(player->vars->mlx, player->vars->win, p_img->img_ptr, 0, 0);
    if (player->m)
    {
        mlx_put_image_to_window(player->vars->mlx, player->vars->win, player->vars->m_fix_img->img_ptr, 0, 0);
        mlx_put_image_to_window(player->vars->mlx, player->vars->win, p_r_img->img_ptr, 0, 0);
    }
    player->p[0] = p_img->img_ptr;
    player->p[1] = p_r_img->img_ptr;
    player->p[2] = NULL;
    ft_collectorclear(player->vars->collector, TMP);
}


float draw_ray(t_player *player, t_data *p_img, int color, t_ray *ray)
{
    (void)p_img;
    (void)color;

    vec1 = find_vertical_iterset(player, ray, vec1);
    vec2 = find_horizontal_iterset(player, ray, vec2);

    ray->v_d_inter = sqrt(ft_pow(vec1->x - player->p_x) + ft_pow(vec1->y - player->p_y));
    ray->h_d_inter = sqrt(ft_pow(vec2->x - player->p_x) + ft_pow(vec2->y - player->p_y));

    if (ray->v_d_inter < ray->h_d_inter)
    {
        if ((ray->angle <= 2 * M_PI && ray->angle > 3 * M_PI / 2) || (ray->angle >= 0 && ray->angle < M_PI / 2))
            ray->side = VERT_R;
        else
            ray->side = VERT_L;
        ray->length = ray->v_d_inter;
    }
    else
    {
        if (ray->angle > 0 && ray->angle < M_PI)
            ray->side = HORZ_D;
        else
            ray->side = HORZ_U;
        ray->length = ray->h_d_inter;
    }
    return 0;
}


// float   draw_ray(t_player *player, t_data *p_img, int color, t_ray *ray)
// {
//     (void)p_img;
//     (void)color;
//     int         v_x;
//     int         v_y;
//     int         h_x;
//     int         h_y;


//     vec1 = find_vertical_iterset(player, ray, vec1);
//     vec2 = find_horizontal_iterset(player, ray, vec2);
    
//     v_x = ft_abs(player->p_x - vec1->x);
//     v_y = ft_abs(player->p_y - vec1->y);
    
//     h_x = ft_abs(player->p_x - vec2->x);
//     h_y = ft_abs(player->p_y - vec2->y);
    
//     if ((v_x < h_x) || (v_y < h_y))
//     {
//         if ((ray->angle < ((2 * M_PI)) && (ray->angle > 3 * (2 * M_PI))))
//             ray->side = VERT_R;
//         else
//             ray->side = VERT_L;
//         draw_line(player, p_img, RED, vec1->x, vec1->y);
//         ray->tex_i = (int)vec1->y % BLOCK;
//         ray->length = sqrt((ft_pow(vec1->x - player->p_x) + ft_pow(vec1->y - player->p_y)));
//         return (0);
//     }
//     else
//     {
//         if ((ray->angle > 0 && ray->angle < M_PI))
//             ray->side = HORZ_D;
//         else
//             ray->side = HORZ_U;
//         draw_line(player, p_img, RED, vec2->x, vec2->y);
//         ray->tex_i = (int)vec2->x % BLOCK;
//         ray->length = sqrt((ft_pow(vec2->x - player->p_x) + ft_pow(vec2->y - player->p_y)));
//         return (0);
//     }
//     ray->length = 0;
//     return (0);
// }

t_ray *cast_rays(t_player *player, t_data *p_img, t_ray *ray)
{
	int i = 0;
    player->t_angle = up_degree(player->angle, -30);

    while (i < WIDTH)
    {
        ray[i].angle = player->t_angle;
        ray[i].t1 = trigo(ray[i].angle, TAN);
        ray[i].t2 = trigo((2 * M_PI) - ray[i].angle, TAN);
        draw_ray(player, p_img, BLUE, &ray[i]);
        player->t_angle = up_degree(player->t_angle, player->f_angle);
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
    int i = 0;

    if ((ray->angle > 0 && ray->angle < M_PI))
    {
        ray->dy = BLOCK;
        ray->dx = (ray->dy / ray->t1);
        vector->y = (ceil(player->p_y / BLOCK) * BLOCK);
        vector->x = player->p_x + ((vector->y - player->p_y) / ray->t1);
        while (i < 36)
        {
            if (!wall_hit_hdn(player, (int)vector->x, (int)vector->y))
                return vector;
            vector->y += ray->dy;
            vector->x += ray->dx;
            i++;
        }
        return vector;
    }
    else if (ray->angle > M_PI && ray->angle < 2 * M_PI)
    {
        ray->dy = -BLOCK;
        ray->dx = (BLOCK / ray->t2);
        vector->y = floor(player->p_y / BLOCK) * BLOCK;
        vector->x = player->p_x + (player->p_y - vector->y) / ray->t2;
        while (i < 36)
        {
            if (!wall_hit_hup(player, (int)vector->x, (int)vector->y))
                return vector;
            vector->x += ray->dx;
            vector->y += ray->dy;
            i++;
        }
        return vector;
    }
    return vector;
}






t_vector *find_vertical_iterset(t_player *player, t_ray *ray, t_vector *vector)
{
    int i = 0;

    if (((ray->angle > (3 * (M_PI / 2))) && (ray->angle <= 2 * (M_PI))) || (((ray->angle >= 0) && (ray->angle < (M_PI / 2)))))
    {
        ray->dx = BLOCK;
        ray->dy = ray->dx * ray->t1;
        vector->x = (ceil(player->p_x/ BLOCK) * BLOCK);
        vector->y = player->p_y + ((vector->x - player->p_x) * ray->t1);
        while (i < 36)
        {
            if (!wall_hit_vrg(player, (int)vector->x, (int)vector->y))
                return (vector);
            vector->x += ray->dx;
            vector->y += ray->dy;
            i++;
        }
        return NULL;
    }
    else if ((ray->angle > (M_PI / 2)) || (ray->angle < 3 * (M_PI / 2)))
    {
        ray->dx = -BLOCK;
        ray->dy = BLOCK * ray->t2;
        vector->x = (floor(player->p_x / BLOCK) * BLOCK);
        vector->y = player->p_y - ((vector->x - player->p_x) * ray->t2);
        while (i < 36)
        {
            if (!wall_hit_vlf(player, (int)vector->x, (int)vector->y))
                return (vector);
            vector->x += ray->dx;
            vector->y += ray->dy;
            i++;
        }
        return (vector);
    }
    return (vector);
}
