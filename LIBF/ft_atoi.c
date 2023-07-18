/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:33:14 by idouni            #+#    #+#             */
/*   Updated: 2023/07/18 16:03:47 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static int	check(int nb, int s)
// {
// 	if (nb > 255 || s == -1)
// 		return (-1);
// 	return (nb);
// }

// int	ft_atoi(const char *str)
// {
// 	int					i;
// 	int					r;
// 	int					s;

// 	s = 1;
// 	r = 0;
// 	i = 0;
// 	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
// 		i++;
// 	while ((str[i] == 45 || str[i] == 43))
// 	{
// 		if (str[i] == 45)
// 			s *= -1;
// 		i++;
// 		if ((str[i] < 48 || str[i] > 57))
// 			return (0);
// 	}
// 	while (str[i] >= 48 && str[i] <= 57)
// 	{
// 		r = r * 10 + (str[i] - 48);
// 		r = check(r, s);
// 		i++;
// 	}
// 	return (r * s);
// }
