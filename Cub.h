#ifndef CUB_H
#define CUB_H

#include <libc.h>
#include <string.h>
#include <math.h>
#include <mlx.h>
#include <fcntl.h>
#include "Get_next_line/get_next_line.h"

#define WIDTH 1800
#define HEIGHT 700

#define BLACK 0x00000000
#define WHITE 0x00FFFFFF
#define BLUE 0x00030DFF

# define ESC         53

# define SP        49

# define M_UP        13
# define M_DN        1
# define M_LF        0
# define M_RG        2

# define K_UP        126
# define K_DN        125
# define K_R         124
# define K_L         123

typedef struct  s_vectorr
{
    int x;
    int y;
}               t_vectorr;

typedef struct  s_vector
{
    float x;
    float y;
}               t_vector;

typedef struct s_player
{
	int		p_x;
	int		p_y;
}		t_player;

typedef struct s_data
{
	void	*img_ptr;
	char	*img_addr;
	int		byte_pixel;
	int		size_line;
	int		endian;
}		t_data;

typedef struct s_collector
{
	void				*addr;
	struct s_collector	*next;
}	t_collector;

typedef struct s_img_collector
{
	void					*img_addr;
	struct s_img_collector	*next;
}	t_img_collector;

typedef struct s_vars 
{
	void			*mlx;
	void			*win;
	char			**map;
	t_vectorr 		*pos;
	t_vector 		*direction;
	t_player		*player;
	t_collector 	**collector;
	t_img_collector	**img_collector;
}	t_vars;


void	debug(void);
int		ft_ext(t_vars *vars);
t_data	*new_image(t_vars *vars);
t_data	*draw_2d_map(t_vars *vars);
int		handler(int key, t_vars *vars);
void	ft_destroy_all_images(t_vars *vars);
int 	mouse_movement(int x, int y, t_vars *vars);
void	ft_collectorclear(t_collector **collector);
char	*ft_mstrdup(t_collector **collector, char *s1);
void	rotate_vector(t_vector *direction, float angle);
void	*h_malloc(t_collector **collector, size_t s, void *p);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void 	draw_player(t_vars *vars, int px, int py, t_vector *direction);
char 	**parse_file(t_collector **collector, int argc, char const *argv[]);
// void 	draw_ray(t_vars *vars, t_vector origin, t_vector direction, int length);
void 	draw_ray(t_data *p_img, t_vars *vars, t_vector origin, t_vector direction, int length);


#endif