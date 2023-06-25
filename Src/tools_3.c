#include "Cub.h"

float   trigo(float angle, t_flag flag)
{
    static int i;

    // printf("angle : %f, index : %d\n",angle ,i++);
    if (flag == COS)
    {
        // printf("COS\n");
        return (cos(angle));
    }
    else if (flag == SIN)
    {
        // printf("SIN\n");
        return (sin(angle));
    }
    else if (flag == TAN)
    {
        // printf("TAN\n");
        return (tan(angle));
    }
}