/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:54:51 by idouni            #+#    #+#             */
/*   Updated: 2023/07/19 17:55:11 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

int ft_ext(t_player *player)
{
    destroy_prev_imges(player);
	destroy_fix_imges(player);
	ft_collectorclear(player->vars->collector, ALL);
	exit(0);
}

float 	deg_to_rad(float angle)
{
    angle = (angle * M_PI / 180);
	return (angle);
}

float 	rad_to_deg(float angle)
{
    angle = (angle * 180 / M_PI);
	return (angle);
}

void rotate_vector(t_vector *direction, float angle)
{
	angle = deg_to_rad(angle);
    float cos_angle = trigo(angle, COS);
    float sin_angle = trigo(angle, SIN);

    float new_x = ((direction->x * cos_angle) - (direction->y * sin_angle));
    float new_y = ((direction->x * sin_angle) + (direction->y * cos_angle));

    direction->x = new_x;
    direction->y = new_y;
}

void	my_mlx_pixel_put(t_player *player, t_data *data, int x, int y, int color)
{
	char *tmp;

	tmp = data->img_addr;
	if(!tmp)
	    exit_with_err(player->vars->collector, MLX);
	tmp = tmp  + (y * data->size_line) + ((data->byte_pixel) * x);
	*(unsigned int *)tmp = color;
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

t_player *	init(int argc, char const *argv[])
{
	static t_collector	*collector;
	t_vars 				*vars;
	t_player 			*player;

	
	collector = NULL;
	player = NULL;
	vars = NULL;
	player = h_malloc(&collector, sizeof(t_player), vars, NTMP);
	vars = NULL;
	vars = h_malloc(&collector, sizeof(t_vars), vars, NTMP);
	vars->collector = &collector;
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "Cub3D");
	if(!vars->mlx || !vars->win)
		exit_with_err(&collector, MLX);
	player->vars = vars;
	vars->dn_c = NULL;
	vars->up_c = NULL;
	vars->lf_c = NULL;
	vars->rg_c = NULL;
	vars->c_color = 0;
    vars->f_color = 0;
	player->angle = 0;
    vars->map = parse_file(player, argc, argv);
	player->color = 0;
	player->vars->fix_img = draw_cf(player);
	player->vars->m_fix_img = draw_2d_map(player);
	player->factor = BLOCK / M_BLOCK;
	player->m = 0;
	player->max_r = sqrt(ft_pow(player->vars->map_h) + ft_pow(player->vars->map_h)) * BLOCK;
    player->f_angle = 60.0/WIDTH;
	player->p = NULL;
	player->p = h_malloc(&collector, 3 * sizeof(void *), player->p, NTMP);
	player->p[0] = NULL;
	vec2 = NULL;
 	vec2 = h_malloc(&collector, sizeof(t_vector), vec2, NTMP);
	vec1 = NULL;
 	vec1 = h_malloc(&collector, sizeof(t_vector), vec1, NTMP);
	vec = NULL;
 	vec = h_malloc(&collector, sizeof(t_vector), vec, NTMP);
	ray = NULL;
	ray = h_malloc(player->vars->collector, (sizeof(t_ray) * WIDTH) + 1, ray, NTMP);
	return (player);
}

t_data 	*draw_player(t_player *player, t_data *p_img)
{
	draw_point(player, p_img, player->p_x/player->factor, player->p_y/player->factor, BLUE);
	draw_line(player, p_img, BLUE, player->p_x + (900 * trigo(player->angle, COS)), player->p_y + (900 * trigo(player->angle, SIN)));
	return (p_img);
}

int hokking(t_player *player)
{
	mlx_hook(player->vars->win, 17, 0, ft_ext, player);
	mlx_hook(player->vars->win, 6, 0, mouse_movement, player);
	mlx_hook(player->vars->win, 2, 1L<<0, handlerp, player);
	mlx_hook(player->vars->win, 3, 1L<<1, handlerr, player);
	updateAndRenderScene(player);
	return (0);
}

void hooks(t_player *player)
{
	mlx_loop_hook(player->vars->mlx, hokking, player);
}

int check_collision(t_player *player, int x, int y)
{
	int k = 0;
	int xo = BLOCK/3;
	int yo = BLOCK/3;

	if (y < 0)
		yo = -BLOCK/3;
	if (x < 0)
		xo = -BLOCK/3;
	if (player->vars->map[(int)(((player->p_y + y + yo)/BLOCK))][(int)(player->p_x/BLOCK)] != '1')
		player->p_y += y;
    else if(player->vars->map[(int)(((player->p_y + yo)/BLOCK))][(int)(player->p_x/BLOCK)] != '1')
		player->p_y += (yo/ft_abs(yo));
	else
		k++;

    if(player->vars->map[(int)(player->p_y/BLOCK)][(int)((player->p_x + x + xo)/BLOCK)] != '1')
		player->p_x += x;
    else if(player->vars->map[(int)(player->p_y/BLOCK)][(int)((player->p_x + xo)/BLOCK)] != '1')
		player->p_x += (xo/(BLOCK/3));
	else
		k++;
	if (k == 2)
		return (0);
	return (1);
}

void draw_point(t_player *player, t_data *img, int x, int y, int color)
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
				my_mlx_pixel_put(player, img, x + i, y + j, color);
                j++;
            }
            i++;
            j = -2;
        }
        i++;
    }
}

float	ft_pow(float n)
{
	return (n * n);
}

float	ft_abs(float n)
{
	if (n < 0)
		n = -n;
	return (n);
}
