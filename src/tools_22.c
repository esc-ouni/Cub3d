/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_22.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 19:30:31 by idouni            #+#    #+#             */
/*   Updated: 2023/08/05 19:43:26 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	*ft_mstrdup(t_collector **collector, const char *s1, t_flag flag)
{
	size_t	i;
	char	*s;

	i = 0;
	s = NULL;
	if (!s1)
		return (NULL);
	s = (char *)h_malloc(collector, sizeof(char) * \
	(ft_strlen(s1) + 1), s, flag);
	while (s1[i] != '\0')
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

// void 	leak()
// {
// 	system("leaks a.out");
// }

// int main(int argc, char const *argv[])
// {
// 	void	*mlx;
// 	void	*xpm;
// 	int		width;
// 	int		height;

// 	atexit(leak);
// 	mlx = mlx_init();
// xpm = mlx_xpm_file_to_image(mlx, "", &width, &height);
// 	if (!xpm)
// 		write(1, "\n\nholllla\n", 11);
// 	free(xpm);
// 	free(mlx);
// 	return 0;
// }
