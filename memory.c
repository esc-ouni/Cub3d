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
	printf("%p\n", p);
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
			printf("%p\n", node->addr);
			free(node->addr);
		}
		free(node);
		node = n_node;
	}
	*collector = NULL;
}

void	debug(void)
{
	printf("\x1B[32m");
	printf("\nDEBUG OK\n");
	printf("\x1B[0m");
}
