#include "Cub.h"

float   trigo(float angle, t_flag flag)
{
    if (flag == COS)
        return (cos(angle));
    else if (flag == SIN)
        return (sin(angle));
    else if (flag == TAN)
        return (tan(angle));
}