/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 10:33:15 by idouni            #+#    #+#             */
/*   Updated: 2023/06/11 17:30:40 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*str_alloc(int fd, char	*str);
char	*r_reset(char *buff);
int		check(char *buff);
int		ft_strlen(char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*line_extract(char *str);

#endif