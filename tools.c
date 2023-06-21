#include "Cub.h"

int ft_ext(t_vars *vars)
{
	ft_destroy_all_images(vars);
	ft_collectorclear(vars->collector, ALL);
	exit(0);
}

float 	deg_to_rad(float angle)
{
    angle = (angle * M_PI / 180);
	return (angle);
}

void rotate_vector(t_vector *direction, float angle)
{
	angle = deg_to_rad(angle);
    float cos_angle = cos(angle);
    float sin_angle = sin(angle);

    float new_x = ((direction->x * cos_angle) - (direction->y * sin_angle));
    float new_y = ((direction->x * sin_angle) + (direction->y * cos_angle));

    direction->x = new_x;
    direction->y = new_y;
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
	player->direction = NULL;
	player->vars = vars;
	player->direction = h_malloc(&collector, sizeof(t_vector), player->direction, NTMP);
	player->p_x = (WIDTH/2);
	player->p_y = (HEIGHT/2);
	player->direction->x = 1;
	player->direction->y = 0;
	player->angle = 0.0001;
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

int check_collision_v2(t_player *player, int x, int y)
{
	int m_y = ((y)/BLOCK);
	int m_x = ((x)/BLOCK);

    printf("p_x : %d, p_y : %d\n",m_x , m_y);    
	if (m_x < 0|| m_y < 0)
		return 0;
	if (m_x > 34|| m_y > 13)
		return 0;
	if (player->vars->map[m_y][m_x] == '0')
		return (1);
	return (0);
}

int check_collision(t_player *player, int x, int y)
{
	int m_y = ((player->p_y + y)/BLOCK);
	int m_x = ((player->p_x + x)/BLOCK);

	if (player->vars->map[m_y][m_x] == '0')
		return (1);
	return (0);
}

void draw_point(t_player *player, int x, int y)
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
                mlx_pixel_put(player->vars->mlx, player->vars->win, x + i, y + j, RED);
                j++;
            }
            i++;
            j = -2;
        }
        i++;
    }
}

void draw_line(t_player *player, t_data *p_img, int color, int x2, int y2)
{
    int i = 0;

    int x1 = (int)player->p_x;
    int y1 = (int)player->p_y;


    float dx = x2 - x1;
    float dy = y2 - y1;
    float steps = fabs(dy);
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
    float x_inc = dx / steps;
    float y_inc = dy / steps;

    float x = x1;
    float y = y1;

    while ( i < 100)
    {
        mlx_pixel_put(player->vars->mlx, player->vars->win, (int)x, (int)y, RED);
		// my_mlx_pixel_put(p_img, (int)x, (int)y, color);
        x += x_inc;
        y += y_inc;
        i++;
    }
}
