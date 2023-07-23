/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:54:51 by idouni            #+#    #+#             */
/*   Updated: 2023/07/23 19:13:44 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

int ft_ext(t_player *plyr)
{
    destroy_prev_imges(plyr);
	destroy_fix_imges(plyr);
	ft_collectorclear(plyr->v->collector, ALL);
	exit(0);
}

float  	deg_to_rad(float  angle)
{
    angle = (angle * M_PI / 180);
	return (angle);
}

float  	rad_to_deg(float  angle)
{
    angle = (angle * 180 / M_PI);
	return (angle);
}

void rotate_vector(t_vector *direction, float  angle)
{
	angle = deg_to_rad(angle);
    float  cos_angle = trigo(angle, COS);
    float  sin_angle = trigo(angle, SIN);

    float  new_x = ((direction->x * cos_angle) - (direction->y * sin_angle));
    float  new_y = ((direction->x * sin_angle) + (direction->y * cos_angle));

    direction->x = new_x;
    direction->y = new_y;
}

void	my_mlx_pixel_put(t_player *plyr, int x, int y, int color)
{
	char *tmp;

	tmp = plyr->t_img->img_addr;
	if(!tmp)
	    exit_with_err(plyr->v->collector, MLX);
	tmp = tmp + (y * plyr->t_img->size_line) + ((plyr->t_img->byte_pixel) * x);
	if (tmp)
		*(int *)tmp = color;
}

char		*ft_mstrdup(t_collector **collector, const char *s1, t_flag flag)
{
	size_t	i;
	char	*s;

	i = 0;
	s = NULL;
	if (!s1)
		return (NULL);
	s = (char *)h_malloc(collector, sizeof(char) * \
	(ft_strlen(s1) + 1), s, flag);
	while (s1[i] != '\0')
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

int	count_alloc_size(t_collector **collector, char const *argv[], int fd)
{
	int size;
	char *s;

	size = 0;
	s = NULL;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	    exit_with_err(collector, OPEN);
	while ((s = get_next_line(fd)))
	{
		free(s);
		s = NULL;
		size++;
	}
	if (close(fd) == -1)
	    exit_with_err(collector, OPEN);
	return (size+=1);
}

t_player *init(int argc, char const *argv[])
{
	static t_collector	*collector;
	t_vars 				*vars;
	t_player 			*plyr;

	
	collector = NULL;
	plyr = NULL;
	vars = NULL;
	plyr = h_malloc(&collector, sizeof(t_player), vars, NTMP);
	vars = NULL;
	vars = h_malloc(&collector, sizeof(t_vars), vars, NTMP);
	vars->collector = &collector;
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "Cub3D");
	if(!vars->mlx || !vars->win)
		exit_with_err(&collector, MLX);
	plyr->v = vars;
	vars->dn_c = NULL;
	vars->up_c = NULL;
	vars->lf_c = NULL;
	vars->rg_c = NULL;
	vars->c_color = 0;
    vars->f_color = 0;
	plyr->angle = 0;
    vars->map = parse_file(plyr, argc, argv);
	plyr->color = 0;
	plyr->v->fix_img = draw_cf(plyr);
	plyr->v->m_fix_img = draw_2d_map(plyr);
	plyr->factor = BLOCK / M_B;
	plyr->m = 0;
    plyr->f_angle = 60.0/WIDTH;
	plyr->mv_sp = (BLOCK/7);
	plyr->p = NULL;
	plyr->p = h_malloc(&collector, 3 * sizeof(void *), plyr->p, NTMP);
	plyr->p[0] = NULL;
	plyr->t_img = NULL;
	plyr->v2 = NULL;
 	plyr->v2 = h_malloc(&collector, sizeof(t_vector), plyr->v2, NTMP);
	plyr->v1 = NULL;
 	plyr->v1 = h_malloc(&collector, sizeof(t_vector), plyr->v1, NTMP);
	plyr->ray = NULL;
	plyr->ray = h_malloc(plyr->v->collector, (sizeof(t_ray) * WIDTH) + 1, plyr->ray, NTMP);
	return (plyr);
}

t_data 	*draw_player(t_player *plyr, t_data *p_img)
{
	plyr->t_img = p_img;
	draw_point(plyr, plyr->p_x/plyr->factor, plyr->p_y/plyr->factor, BLUE);
	draw_line(plyr, BLUE, plyr->p_x + ((BLOCK/0.9) * trigo(plyr->angle, COS)), plyr->p_y + ((BLOCK/0.9) * trigo(plyr->angle, SIN)));
	return (p_img);
}

int hokking(t_player *plyr)
{
	mlx_hook(plyr->v->win, 17, 0, ft_ext, plyr);
	mlx_hook(plyr->v->win, 6, 0, mouse_movement, plyr);
	mlx_hook(plyr->v->win, 2, 1L<<0, handlerp, plyr);
	mlx_hook(plyr->v->win, 3, 1L<<1, handlerr, plyr);
	updateAndRenderScene(plyr);
	return (0);
}

void check_collision(t_player *plyr, float x, float y)
{
    int xo = BLOCK/4;
    int yo = BLOCK/4;

    if (y < 0)
        yo = -BLOCK/4;
    if (x < 0)
        xo = -BLOCK/4;

    if(plyr->v->map[(int)(((plyr->p_y + y)/BLOCK))][(int)((plyr->p_x)/BLOCK)] != '1' && plyr->v->map[(int)(((plyr->p_y + y + yo/2)/BLOCK))][(int)((plyr->p_x + xo/2)/BLOCK)] != '1')
    {
        if (plyr->v->map[(int)(((plyr->p_y + y + yo)/BLOCK))][(int)((plyr->p_x + xo)/BLOCK)] != '1')
            plyr->p_y += y;  
    }

    if(plyr->v->map[(int)((plyr->p_y)/BLOCK)][(int)((plyr->p_x + x)/BLOCK)] != '1' && plyr->v->map[(int)((plyr->p_y + yo/2)/BLOCK)][(int)((plyr->p_x + x + xo/2)/BLOCK)] != '1')
    {
        if(plyr->v->map[(int)((plyr->p_y + yo)/BLOCK)][(int)((plyr->p_x + x + xo)/BLOCK)] != '1')
            plyr->p_x += x;
    }
}

void draw_point(t_player *plyr, int x, int y, int color)
{
    int i, j;

    i = -2;
    j = -2; 
    while (i < 4)
    {
        while(i < 2)
        {
            while(j < 2)
            {
				my_mlx_pixel_put(plyr, x + i, y + j, color);
                j++;
            }
            i++;
            j = -2;
        }
        i++;
    }
}

float 	ft_pow(float  n)
{
	return (n * n);
}

float 	ft_abs(float  n)
{
	if (n < 0)
		n = -n;
	return (n);
}
