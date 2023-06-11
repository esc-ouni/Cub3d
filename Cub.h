#ifndef CUB_H
#define CUB_H

#include <libc.h>
#include <mlx.h>
#include <fcntl.h>
#include "Get_next_line/get_next_line.h"

#define WIDTH 2000
#define HEIGHT 800

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

typedef struct s_player
{
	void	*img_ptr;
	char	*img_addr;
	int		byte_pixel;
	int		size_line;
	int		endian;
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
	t_player		*player;
	t_collector 	**collector;
	t_img_collector	**img_collector;
}	t_vars;

int		ft_ext(t_vars *vars);
void	move_up(t_vars *vars);
void	move_dn(t_vars *vars);
void	move_lf(t_vars *vars);
void	move_rg(t_vars *vars);
t_data	*new_image(t_vars *vars);
void	draw_2d_map(t_vars *vars);
int		handler(int key, t_vars *vars);
void	draw_in_image(t_vars *vars, int i);
void	ft_collectorclear(t_collector **collector);
char	*ft_mstrdup(t_collector **collector, char *s1);
void	*h_malloc(t_collector **collector, size_t s, void *p);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	ft_destroy_all_images(t_vars *vars);

#endif