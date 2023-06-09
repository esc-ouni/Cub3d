#include "Cub.h"

void	*h_malloc(t_collector **collector, size_t s, void *p)
{
	t_collector	*tmp;
	t_collector	*new_node;

	new_node = malloc(sizeof(t_collector));
	p = malloc(s);
	if (!new_node || !p)
	{
		write (2, "\033[0;32mMALLOC_FAILED\033[0;37m\n", 29);
		ft_collectorclear(collector);
		exit (1);
	}
	new_node->addr = p;
	printf("alloc     : %p\n", p);
	if (!(*collector))
	{
		*collector = new_node;
		new_node->next = NULL;
	}
	else
	{
		tmp = *collector;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
		new_node->next = NULL;
	}
	return (p);
}


void	ft_collectorclear(t_collector **collector)
{
	t_collector	*node;
	t_collector	*n_node;

	if (!(*collector) || !collector)
		return ;
	node = *collector;
	while (node)
	{
		n_node = node->next;
		if (node->addr)
		{
			printf("free      : %p\n", node->addr);
			free(node->addr);
		}
		free(node);
		node = NULL;
		node = n_node;
	}
	*collector = NULL;
}

void	new_image(t_vars *vars)
{
	void			*p;
	t_img_collector	*tmp;
	t_img_collector	*new_node;

	p = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	new_node = NULL;
	new_node = h_malloc(vars->collector, sizeof(t_img_collector), new_node);
	if (!p)
	{
		write (2, "\033[0;32mMLX_NEW_IMAGE_FAILED\033[0;37m\n", 29);
		ft_destroy_all_images(vars);
		ft_collectorclear(vars->collector);
		exit (1);
	}
	new_node->img_addr = p;
	printf("new image : %p\n", new_node->img_addr);
	if (!(*(vars->img_collector)))
	{
		*(vars->img_collector) = new_node;
		new_node->next = NULL;
	}
	else
	{
		tmp = *(vars->img_collector);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
		new_node->next = NULL;
	}

}

void	ft_destroy_all_images(t_vars *vars)
{
	t_img_collector	**collector;
	t_img_collector	*node;

	mlx_destroy_window(vars->mlx, vars->win);
	collector = vars->img_collector;
	if (!(*collector) || !collector)
		return ;
	node = *collector;
	while (node)
	{
		if (node->img_addr)
		{
			printf("des image : %p\n", node->img_addr);
			mlx_destroy_image(vars->mlx, node->img_addr);
		}
		node = node->next;
	}
	*collector = NULL;
}
void	debug(void)
{
	printf("\x1B[32m");
	printf("\nDEBUG OK\n");
	printf("\x1B[0m");
}
