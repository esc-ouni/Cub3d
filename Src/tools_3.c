/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:54:44 by idouni            #+#    #+#             */
/*   Updated: 2023/07/07 11:47:43 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

void    exit_with_err(t_collector **collector, t_flag cause)
{
    if (cause == MALLOC)
        write (2, "\033[0;32mError\nMALLOC_FAILED\033[0;37m\n", 35);
    else if (cause == PARSE)
        write (2, "\033[0;32mError\nMISCONFIGURATION_OF_.cub_FILE\033[0;37m\n", 51);
    else if (cause == ARGS)
        write (2, "\033[0;32mError\nNOT_A_VALID_ARGS_NUMBER\033[0;37m\n", 51);
    else if (cause == MLX)
		write (2, "\033[0;32mError\nMLX_FAILED\033[0;37m\n", 32);
    else if (cause == OPEN)
		write (2, "\033[0;32mError\nUNABLE_TO_OPEN_A_FILE\033[0;37m\n", 43);
    else if (cause == MAP)
		write (2, "\033[0;32mError\nINCOMPATIBLE_SIZE\033[0;37m\n", 39);
    ft_collectorclear(collector, ALL);
    exit (1);
}

void    check_dups(t_collector **collector, int argc, char const *argv[])
{
    int fd;

    fd = 0;
    if (fd == -1)
        exit_with_err(collector, OPEN);

}
void    check_errs(t_collector **collector, int argc, char const *argv[])
{
    if(ft_strlen(strstr(argv[1], ".cub")) != 4)
        exit_with_err(collector, PARSE);
}
void    check_map(t_collector **collector, int argc, char const *argv[])
{
}

char **get_map(t_collector **collector, int argc, char const *argv[])
{
	int	    fd;
	char    **map;
	char    *s;
	int     i;
	int     i2;
    int     itsmap;

    itsmap = 0;
	i = 0;
	i2 = 0;
	fd = 0;
	map = NULL;  
    map = h_malloc(collector, (count_alloc_size(collector, fd) * sizeof(char *)), map, NTMP);
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        exit_with_err(collector, OPEN);
    while((s = get_next_line(fd))) //not appopriate
    {
        if(strcmp("0", s) || strcmp("1", s))
            itsmap = 1;
        if (itsmap)
        {
            map[i2] = ft_mstrdup(collector, s);
            i2++;
        }
        free(s);
        s = NULL;
        i++;
    }
    map[i2] = NULL;
    return (map);
}

char **parse_file(t_collector **collector, int argc, char const *argv[])
{
    char **map;
    int fd;

    fd = 0;
	if (argc == 2 && argv[1])
	{
        fd = open(argv[1], O_RDONLY);
        if (fd == -1)
            exit_with_err(collector, OPEN);
        map = get_map(collector, argc, argv);
        check_errs(collector, argc, argv);
        // check_dups();
        // check_map();  
        return (map);
	}
    exit_with_err(collector, ARGS);
    return (NULL);
}

float   trigo(float angle, t_flag flag)
{
    // static int i;

    // printf("angle : %f, index : %d\n",rad_to_deg(angle) ,i++);
    if (flag == COS)
    {
        // printf("COS\n");
        return (cos(angle));
    }
    else if (flag == SIN)
    {
        // printf("SIN\n");
        return (sin(angle));
    }
    else if (flag == TAN)
    {
        // printf("TAN\n");
        return (tan(angle));
    }
    return(0);
}
