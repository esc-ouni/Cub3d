#include "Cub.h"

void draw_ray(t_player *player, t_data *p_img, int color)
{
    t_ray *ray;
    ray = NULL;
    
    ray = h_malloc(player->vars->collector, sizeof(t_ray), ray,  NTMP);

    ray->p_x = player->p_x;
    ray->p_y = player->p_y;

    ray->angle = player->angle;
    // ray->direction = player->direction;


    int x1 = (int)player->p_x;
    int y1 = (int)player->p_y;
    int x2 = (int)(player->p_x + player->direction->x * 200);
    int y2 = (int)(player->p_y + player->direction->y * 200);

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
    ray->p_x = player->p_x;
    ray->p_y = player->p_y;

	mlx_put_image_to_window(player->vars->mlx, player->vars->win, p_img->img_ptr, 0, 0);
    printf("player angle :%f\n",  player->angle);
    printf("ray    angle :%f\n\n",  ray->angle);
    find_horizontal_iterset(player, ray);
    find_vertical_iterset(player, ray);
    printf("\n");
}

t_data 	*cast_rays(t_player *player, t_data *p_img)
{
	int k = 0;
	float tmpx;
	float tmpy;


	tmpx = player->direction->x;
	tmpy = player->direction->y;

    draw_ray(player, p_img, RED);
    // rotate_vector(player->direction, -30);
    // while (k < 600)
    // {
    //     rotate_vector(player->direction, 0.1);
    //     draw_ray(player, p_img, BLUE);
    //     k++;
    // }
	player->direction->x = tmpx;
	player->direction->y = tmpy;
	return (p_img);
}

t_vector *find_horizontal_iterset(t_player *player, t_ray *ray)
{
	t_vector *vector;
    int i = 0;
    float    stepy = BLOCK;
    float    stepx = (stepy / tan(player->angle));

    int f, j, k, x, y;
	vector = NULL;

	vector = h_malloc(player->vars->collector, sizeof(t_vector), vector, NTMP);
    if ((ray->angle >= 0 && ray->angle <= M_PI))
    {
        vector->y = (int)player->p_y;
        vector->x = player->p_x + ((player->p_y - vector->y) / tan(player->angle));
        while (i < 5)
        {
            printf("Horizontal inersect, x : %d, y : %d\n", (int)(vector->x), (int)(vector->y));

            f = -5;
            j = -5; 
            k = 0; 

            x = player->p_x;
            y = player->p_y;
            while(f < 5)
            {
                while(j < 5)
                {
                    mlx_pixel_put(player->vars->mlx, player->vars->win, (vector->x) + f, (vector->y) + j, BLUE);
                    j++;
                }
                f++;
                j = -5;
            }
            vector->x += stepx;
            vector->y += stepy;
            i++;
        }
        return (NULL);
    }
    else
    {
        vector->y = (int)player->p_y + 1;
        vector->x = player->p_x + ((player->p_y - vector->y) / tan(player->angle));
        while (i < 5)
        {
            printf("Horizontal inersect, x : %d, y : %d\n", (int)(vector->x), (int)(vector->y));

            f = -5;
            j = -5; 
            k = 0; 

            x = player->p_x;
            y = player->p_y;
            while(f < 5)
            {
                while(j < 5)
                {
                    mlx_pixel_put(player->vars->mlx, player->vars->win, (vector->x) + f, (vector->y) + j, BLUE);
                    j++;
                }
                f++;
                j = -5;
            }
            vector->x -= stepx;
            vector->y -= stepy;
            i++;
        }
        return (NULL);
    }
    return (vector);
}

t_vector *find_vertical_iterset(t_player *player, t_ray *ray)
{
	t_vector *vector;
    int i = 0;
    float    stepx = BLOCK;
    float    stepy = (stepx * tan(player->angle));

    int f, j, k, x, y;
	vector = NULL;

	vector = h_malloc(player->vars->collector, sizeof(t_vector), vector, NTMP);
    if ((ray->angle >= 0 && ray->angle <= (M_PI / 2)) ||(ray->angle >= 4.71 && ray->angle <= 7 ))
    {
        vector->x = (int)player->p_x + 1;
        vector->y = player->p_y - ((vector->x - player->p_x) * tan (player->angle));
        while (i < 5)
        {
            printf("Vertical inersect, x : %d, y : %d\n", (int)(vector->x), (int)(vector->y));

            f = -5;
            j = -5; 
            k = 0; 

            x = player->p_x;
            y = player->p_y;
            while(f < 5)
            {
                while(j < 5)
                {
                    mlx_pixel_put(player->vars->mlx, player->vars->win, (vector->x) + f, (vector->y) + j, BLUE);
                    j++;
                }
                f++;
                j = -5;
            }
            vector->x += stepx;
            vector->y += stepy;
            i++;
        }
        return NULL;
    }
    else
    {
        vector->x = (int)player->p_x;
        vector->y = player->p_y - ((vector->x - player->p_x) * tan (player->angle));
        while (i < 5)
        {
            printf("Vertical inersect, x : %d, y : %d\n", (int)(vector->x), (int)(vector->y));

            f = -5;
            j = -5; 
            k = 0; 

            x = player->p_x;
            y = player->p_y;
            while(f < 5)
            {
                while(j < 5)
                {
                    mlx_pixel_put(player->vars->mlx, player->vars->win, (vector->x) + f, (vector->y) + j, BLUE);
                    j++;
                }
                f++;
                j = -5;
            }
            vector->x -= stepx;
            vector->y -= stepy;
            i++;
        }   
        return NULL;
    }
    return (vector);
}
