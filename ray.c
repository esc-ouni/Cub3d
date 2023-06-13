#include "Cub.h"

void draw_ray(void *mlx_ptr, void *win_ptr, t_vector origin, t_vector direction, int length, int color)
{
    int x1 = (int)origin.x;
    int y1 = (int)origin.y;
    int x2 = (int)(origin.x + direction.x * length);
    int y2 = (int)(origin.y + direction.y * length);

    float dx = x2 - x1;
    float dy = y2 - y1;
    float steps = fmax(fabs(dx), fabs(dy));
    float x_inc = dx / steps;
    float y_inc = dy / steps;

    float x = x1;
    float y = y1;

    for (int i = 0; i < steps; i++)
    {
        mlx_pixel_put(mlx_ptr, win_ptr, (int)x, (int)y, color);
        x += x_inc;
        y += y_inc;
    }
}
