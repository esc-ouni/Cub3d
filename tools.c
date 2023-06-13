#include "Cub.h"

int ft_ext(t_vars *vars)
{
	ft_destroy_all_images(vars);
	ft_collectorclear(vars->collector);
	exit(0);
}
void rotate_vector(t_vector *direction, float angle)
{
    float rad_angle = angle * M_PI / 180.0;
    float cos_angle = cos(rad_angle);
    float sin_angle = sin(rad_angle);

    float new_x = direction->x * cos_angle - direction->y * sin_angle;
    float new_y = direction->x * sin_angle + direction->y * cos_angle;

    direction->x = new_x;
    direction->y = new_y;
}

int	handler(int key, t_vars *vars)
{
	
	static int px;
	static int py;
	static int r = 10;

	if (key == 53 || key == 17)
	{
		ft_destroy_all_images(vars);
		ft_collectorclear(vars->collector);
		exit(0);
	}
	// else if (key == K_UP)
	// 	move_up(vars);
	// else if (key == K_DN)
	// 	move_dn(vars);

	if (key == K_R)
	{
		rotate_vector(vars->direction, 5);
		draw_player(vars, px, py, vars->direction);
	}
	else if (key == K_L)
	{
		rotate_vector(vars->direction, -5);
		draw_player(vars, px, py, vars->direction);
	}

	if (key == M_RG)
	{
		if (vars->map[(((HEIGHT/2) + py)/50)][(((WIDTH/2) + px + r)/50)] == '0')
			draw_player(vars, (px += r), py, vars->direction);
	}
	if (key == M_DN)
	{
		if (vars->map[(((HEIGHT/2) + py + r)/50)][(((WIDTH/2) + px)/50)] == '0')
			draw_player(vars, px, (py += r), vars->direction);
	}
	if (key == M_LF)
	{
		if (vars->map[(((HEIGHT/2) + py)/50)][(((WIDTH/2) + px - r)/50)] == '0')
			draw_player(vars, (px -= r), py, vars->direction);
	}
	if (key == M_UP)
	{
		if (vars->map[(((HEIGHT/2) + py - r)/50)][(((WIDTH/2) + px)/50)] == '0')
			draw_player(vars, px, (py -= r), vars->direction);
	}

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
	(ft_strlen(s1) + 1), s);
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
		map = h_malloc(collector, (count_alloc_size(fd) * sizeof(char *)), map);
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
		// i = 0;
		// while(*map)
		// 	printf("%s\n", *(map)++);
		return (map);
	}
	exit(EXIT_FAILURE);
}
