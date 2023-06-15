#include "Cub.h"

int ft_ext(t_vars *vars)
{
	ft_destroy_all_images(vars);
	ft_collectorclear(vars->collector, ALL);
	exit(0);
}
void rotate_vector(t_vector *direction, float angle)
{
	if (angle < 0)
		angle += 360;
    float rad_angle = ((angle * PI) / 180);
    float cos_angle = cos(rad_angle);
    float sin_angle = sin(rad_angle);

    float new_x = ((direction->x * cos_angle) - (direction->y * sin_angle));
    float new_y = ((direction->x * sin_angle) + (direction->y * cos_angle));

    direction->x = new_x;
    direction->y = new_y;
}

int mouse_movement(int x, int y, t_vars *vars)
{
	static int last_pos;

	if (x <= 1800 && x >= 0)
	{
		if (x >= last_pos)
		{
			rotate_vector(vars->direction, ((x - last_pos)/3));
			draw_player(vars, 0, 0, vars->direction, vars->angle);
			draw_player(vars, vars->pos->x, vars->pos->y, vars->direction, vars->angle);
			last_pos = x;
			vars->angle += ((x - last_pos)/3);  
		}
		else if (x < last_pos)
		{
			rotate_vector(vars->direction, ((x - last_pos)/3));
			draw_player(vars, 0, 0, vars->direction, vars->angle);
			draw_player(vars, vars->pos->x, vars->pos->y, vars->direction, vars->angle);
			last_pos = x;
			vars->angle += ((x - last_pos)/3);  
		}
	}
	// ft_collectorclear(vars->collector, TMP);
	return(0);
}

int	handler(int key, t_vars *vars)
{
	
	static int px;
	static int py;
	static int r = 10;

	if (key == 53 || key == 17)
	{
		ft_destroy_all_images(vars);
		ft_collectorclear(vars->collector, ALL);
		exit(0);
	}
	if (key == K_R)
	{
		// rotate_vector(vars->direction, 4.5);
		rotate_vector(vars->direction, 4.5);
		draw_player(vars, px, py, vars->direction, vars->angle);
		// vars->angle += 4.5;  
		// vars->pos->x = px;
		// vars->pos->y = py;
	}
	else if (key == K_L)
	{
		// rotate_vector(vars->direction, -4.5);
		rotate_vector(vars->direction, -4.5);
		draw_player(vars, px, py, vars->direction, vars->angle);
		// vars->angle -= 4.5;
		// vars->pos->x = px;
		// vars->pos->y = py;
	}

	if (key == M_RG)
	{
		if (vars->map[(((HEIGHT/2) + py)/BLOCK)][(((WIDTH/2) + px + r)/BLOCK)] == '0')
		{
			vars->pos->x = px + r;
			vars->pos->y = py;
			draw_player(vars, (px += r), py, vars->direction, vars->angle);
		}
	}
	if (key == M_DN)
	{
		if (vars->map[(((HEIGHT/2) + py + r)/BLOCK)][(((WIDTH/2) + px)/BLOCK)] == '0')
		{
			vars->pos->x = px;
			vars->pos->y = py + r;
			draw_player(vars, px, (py += r), vars->direction, vars->angle);
		}
	}
	if (key == M_LF)
	{
		if (vars->map[(((HEIGHT/2) + py)/BLOCK)][(((WIDTH/2) + px - r)/BLOCK)] == '0')
		{
			vars->pos->x = px - r;
			vars->pos->y = py;
			draw_player(vars, (px -= r), py, vars->direction, vars->angle);
		}
	}
	if (key == M_UP)
	{
		if (vars->map[(((HEIGHT/2) + py - r)/BLOCK)][(((WIDTH/2) + px)/BLOCK)] == '0')
		{
			vars->pos->x = px;
			vars->pos->y = py - r;
			draw_player(vars, px, (py -= r), vars->direction, vars->angle);
		}
	}
	// ft_collectorclear(vars->collector, TMP);
	return(0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	(void)color;
	char *tmp;

	tmp = data->img_addr;
	if(!tmp)
		exit(EXIT_FAILURE);
	tmp = tmp + (y * data->size_line) + ((data->byte_pixel) * x);
	*(unsigned int *)tmp = color;
}

char	*ft_mstrdup(t_collector **collector, char *s1)
{
	size_t	i;
	char	*s;

	i = 0;
	s = NULL;
	if (!s1)
		return (NULL);
	s = (char *)h_malloc(collector, sizeof(char) * \
	(ft_strlen(s1) + 1), s, NTMP);
	while (s1[i] != '\0')
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

int	count_alloc_size(fd)
{
	int size;
	char *s;

	size = 0;
	s = NULL;
	fd = open("/Users/idouni/Desktop/789/map.Cub", O_RDONLY);
	if (fd == -1)
		exit(EXIT_FAILURE);
	while ((s = get_next_line(fd)))
	{
		free(s);
		s = NULL;
		size++;
	}
	if (close(fd) == -1)
		exit(EXIT_FAILURE);
	return (size+=1);
}


char **parse_file(t_collector **collector, int argc, char const *argv[])
{
	int	fd;
	char **map;
	char *s;
	int i;

	i = 0;
	fd = 0;
	map = NULL;
	if (argc && argv[0])   //to_prot
	{
		map = h_malloc(collector, (count_alloc_size(fd) * sizeof(char *)), map, NTMP);
		fd = open("/Users/idouni/Desktop/789/map.Cub", O_RDONLY);
		if (fd == -1)
			exit(EXIT_FAILURE);
		while((s = get_next_line(fd)))
		{
			map[i] = ft_mstrdup(collector, s);
			free(s);
			s = NULL;
			i++;
		}
		map[i] = NULL;
		return (map);
	}
	exit(EXIT_FAILURE);
}
