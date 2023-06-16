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

// int mouse_movement(int x, int y, t_vars *vars)

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

t_player *init(int argc, char const *argv[])
{
	static t_collector *collector;
	static t_img_collector *img_collector;
	t_vars 		*vars;
	t_player 	*player;

	
	collector = NULL;
	img_collector = NULL;

	player = NULL;
	player = h_malloc(&collector, sizeof(t_player), vars, NTMP);
	vars = NULL;
	vars = h_malloc(&collector, sizeof(t_vars), vars, NTMP);
	vars->img_collector = &img_collector;
	vars->collector = &collector;
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "Cub");
    vars->map = parse_file(&collector, argc, argv);
	if(!vars->mlx || !vars->win)
	{
		write (2, "\033[0;32mMLX_FAILED\033[0;37m\n", 29);
		ft_destroy_all_images(vars);
		ft_collectorclear(vars->collector, ALL);
		exit (1);
	}
	player->vars = vars;
	player->p_x = (WIDTH/2);
	player->p_y = (HEIGHT/2);
	return (player);
}

t_data 	*draw_player(t_player *player, t_data *p_img)
{
	int i, j, k, x, y;

	i = -5;
	j = -5; 
	k = 0; 

	x = (int)player->p_x;
	y = (int)player->p_y;
	printf("x : %d, y : %d\n", x, y);
	while(i < 5)
	{
		while(j < 5)
		{
			my_mlx_pixel_put(p_img, x + i, y + j, BLUE);
			j++;
		}
		i++;
		j = -5;
	}
	return (p_img);
}

void hooks(t_player *player)
{
	mlx_hook(player->vars->win, 17, 0, ft_ext, player);
	mlx_hook(player->vars->win, 2, 1L << 0, handler, player);
	// mlx_hook(player->vars->win, 6, 0, mouse_movement, player);
	mlx_loop(player->vars->mlx);
}
