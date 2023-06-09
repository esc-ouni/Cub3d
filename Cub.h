#ifndef CUB_H
#define CUB_H

#include <libc.h>
#include <mlx.h>

typedef struct s_collector
{
	void				*addr;
	struct s_collector	*next;
}	t_collector;

typedef struct s_vars 
{
	void		*mlx;
	void		*win;
	t_collector **collector;
}	t_vars;

int		ft_ext(t_vars *vars);
int		handler(int key, t_vars *vars);
void	ft_collectorclear(t_collector **collector);
void	*h_malloc(t_collector **collector, size_t s, void *p);

#endif