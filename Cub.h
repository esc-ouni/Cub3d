#ifndef CUB_H
#define CUB_H

#include <libc.h>
#include <mlx.h>

#define WIDTH 2000
#define HEIGHT 800

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
	t_collector 	**collector;
	t_img_collector	**img_collector;
}	t_vars;

int		ft_ext(t_vars *vars);
void	*new_image(t_vars *vars);
int		handler(int key, t_vars *vars);
void	ft_collectorclear(t_collector **collector);
void	*h_malloc(t_collector **collector, size_t s, void *p);
void	ft_destroy_all_images(t_vars *vars);

#endif