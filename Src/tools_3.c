#include "Cub.h"

float   trigo(float angle, t_flag flag)
{
    static int i;

    // printf("angle : %f, index : %d\n",rad_to_deg(angle) ,i++);
    if (flag == COS)
    {
        // printf("COS\n\n");
        return (cos(angle));
    }
    else if (flag == SIN)
    {
        // printf("SIN\n\n");
        return (sin(angle));
    }
    else if (flag == TAN)
    {
        // printf("TAN\n\n");
        return (tan(angle));
    }
    return(0);
}