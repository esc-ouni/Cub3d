#ifndef CUB_H
#define CUB_H

#include <libc.h>
#include <string.h>
#include <math.h>
#include <mlx.h>
#include <fcntl.h>
#include "Get_next_line/get_next_line.h"

#define NORTH 90
#define EAST  0
#define SOUTH 270
#define WEST  180

#define WIDTH 1800
#define HEIGHT 700
#define BLOCK 50
#define PI 3.14159265

#define BLACK 0x00000000
#define WHITE 0x00FFFFFF
#define BLUE 0x00030DFF
#define RED 0x00FF0D03

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

typedef enum e_flag
{
	TMP,
	NTMP,
	ALL
}	t_flag;

typedef struct s_ntmp
{
	void			*ntmp_addr;
	struct s_ntmp	*next;
}	t_ntmp;

typedef struct s_tmp
{
	void			*tmp_addr;
	struct s_tmp	*next;
}	t_tmp;

typedef struct s_collector
{
	t_tmp				*tmp_cltr;
	t_ntmp				*ntmp_cltr;
}	t_collector;

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



typedef struct s_data
{
	void	*img_ptr;
	char	*img_addr;
	int		byte_pixel;
	int		size_line;
	int		endian;
}		t_data;

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
	t_collector 	**collector;
	t_img_collector	**img_collector;
}	t_vars;

typedef struct s_player
{
	float		p_x;
	float		p_y;
	float		angle;
	t_vector 	*direction;
	t_vars	*vars;
}		t_player;

typedef struct s_ray
{
	float		length;
	float		p_x;
	float		p_y;
	float		angle;
	t_vector 	*direction;
	t_vars	*vars;
}		t_ray;

float 		deg_to_rad(float angle);
t_player	*init(int argc, char const *argv[]);
void		hooks(t_player *player);
int			handler(int key, t_player *player);
void 		update_scene(t_player *player);
t_data		*draw_2d_map(t_player *player);
t_data 		*cast_rays(t_player *player, t_data *p_img);
void 		draw_ray(t_player *player, t_data *p_img, int color);
void 		rotate_vector(t_vector *direction, float angle);
int 		mouse_movement(int x, int y, t_player *player);
t_vector 	*find_horizontal_iterset(t_player *player, t_ray *ray);
int 		check_collision(t_player *player, int x, int y);

void	debug(void);
int		ft_ext(t_vars *vars);
t_data	*new_image(t_vars *vars);
void	free_tmp(t_collector **collector);
void	free_ntmp(t_collector **collector);
void	ft_destroy_all_images(t_vars *vars);
void	head_alloc(t_collector **collector);
char	*ft_mstrdup(t_collector **collector, char *s1);
void	tmp_alloc(t_collector **collector, size_t s, void **p);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	ft_collectorclear(t_collector **collector, t_flag flag);
void	ntmp_alloc(t_collector **collector, size_t s, void **p);
void	*h_malloc(t_collector **collector, size_t s, void *p, t_flag flag);
char 	**parse_file(t_collector **collector, int argc, char const *argv[]);
t_data	*draw_player(t_player *player, t_data *p_img);


#endif