/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 10:33:15 by idouni            #+#    #+#             */
/*   Updated: 2023/07/27 21:42:11 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 1
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*str_alloc(int fd, char	*str);
char	*r_reset(char *buff);
int		g_check(char *buff);
int		ft_gstrlen(char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*line_extract(char *str);

#endif
