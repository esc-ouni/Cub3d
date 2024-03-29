/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_8.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:23:31 by idouni            #+#    #+#             */
/*   Updated: 2023/08/05 17:21:56 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static size_t	count_str(char const *s, char c)
{
	size_t	i;
	size_t	t;
	size_t	count;

	i = 0;
	t = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && t == 0)
		{
			t = 1;
			count++;
		}
		else if (s[i] == c)
			t = 0;
		i++;
	}
	return (count);
}

static size_t	lenfinder(char const *s, char c, int start)
{
	size_t	i;

	i = 0;
	while (s[start + i] || s[start + i] == '\0')
	{
		if (s[start + i] == c || s[start + i] == '\0')
			return (i);
		i++;
	}
	return (0);
}

static char	**ft_msplitp2(t_vars *vars, char **p, \
char const *s, char const c)
{
	size_t		i;
	size_t		l;
	size_t		l_s;
	size_t		i2;

	i = 0;
	i2 = 0;
	l_s = ft_strlen(s);
	while (i < l_s)
	{
		if (s[i] != c)
		{
			l = lenfinder(s, c, i);
			p[i2] = ft_msubstr(vars, s, i, l);
			if (p[i2] == NULL)
				return (NULL);
			i2++;
			i += l;
		}
		i++;
	}
	p[i2] = NULL;
	return (p);
}

char	**ft_msplit(t_vars *vars, char const *s, char const c, t_flag flag)
{
	size_t		n;
	char		**p;

	p = NULL;
	if (!s)
		return (NULL);
	n = count_str(s, c);
	p = (char **)h_malloc(vars->collector, sizeof (char *) * (n + 1), p, flag);
	if (p)
	{
		p = ft_msplitp2(vars, p, s, c);
		return (p);
	}
	return (NULL);
}
