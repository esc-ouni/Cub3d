/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:54:44 by idouni            #+#    #+#             */
/*   Updated: 2023/07/10 10:13:50 by idouni           ###   ########.fr       */
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

void    check_dups(t_collector **collector, char **map, char const *argv[], t_player *player)
{
    (void)map;
    (void)player;
    // int so;
    // int no;
    // int we;
    // int ea;
    int fd;

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        exit_with_err(collector, OPEN);
    

}
void    check_errs(t_collector **collector, int argc, char const *argv[])
{
    (void)argc;
    if(ft_strlen(strstr(argv[1], ".cub")) != 4)
        exit_with_err(collector, PARSE);
}
void    check_map(t_collector **collector, char **map)
{
    (void)map;
    (void)collector;   
}

char **get_map(t_collector **collector, int argc, char const *argv[], int t)
{
    (void)argc;

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
        if(i == t)
            itsmap = 1;
        if (itsmap)
        {
            map[i2] = ft_mstrdup(collector, s, NTMP);
            i2++;
        }
        free(s);
        s = NULL;
        i++;
    }
    map[i2] = NULL;
    return (map);
}

int extract_color(t_player *player, char *color)
{
    char **s;
    int color_c;

    color_c = 0;
    color = ft_mstrtrim(player->vars, color, " ", TMP);
    s = ft_msplit(player->vars, color, ',', TMP);

    color_c = ft_atoi(*s);
    color_c <<= 8;
    s++;
    color_c |= ft_atoi(*s);
    color_c <<= 8;
    s++;
    color_c |= ft_atoi(*s);
    return (color_c);
}

int    get_elem(t_collector **collector, char const *argv[], t_player *player)
{
    char *s;
    int fd;
    int i = 0;;

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        exit_with_err(collector, OPEN);
    while((s = get_next_line(fd))) //not appopriate
    {
        if (strnstr(s, "NO", 2))
            player->vars->up_c = ft_mstrdup(collector, s+3, TMP);
        else if (strnstr(s, "SO", 2))
            player->vars->dn_c = ft_mstrdup(collector, s+3, TMP);
        else if (strnstr(s, "WE", 2))
            player->vars->rg_c = ft_mstrdup(collector, s+3, TMP);
        else if (strnstr(s, "EA", 2))
            player->vars->lf_c = ft_mstrdup(collector, s+3, TMP);
        else if (strnstr(s, "F", 1))
            player->vars->f_color = extract_color(player, s+1);
        else if (strnstr(s, "C", 1))
            player->vars->c_color = extract_color(player, s+1);
        else if (strnstr(s, "111", ft_strlen(s)))
        {
            free(s);
            return  i;
        }
        free(s);
        i++;
        s = NULL;
    }
    return (0);
}

int    get_elements(t_collector **collector, char const *argv[], t_player *player)
{
    int i = 0;
    // int fd;

    // fd = open(argv[1], O_RDONLY);
    // if (fd == -1)
    //     exit_with_err(collector, OPEN);

    i = get_elem(collector, argv, player);
    
	player->vars->up = new_image_from_xpm(player, player->vars->up_c);
	player->vars->dn = new_image_from_xpm(player, player->vars->dn_c);
	player->vars->lf = new_image_from_xpm(player, player->vars->lf_c);
	player->vars->rg = new_image_from_xpm(player, player->vars->rg_c);
    return (i);
}

char **parse_file(t_collector **collector, int argc, char const *argv[], t_player *player)
{
    char **map;
    int fd;
    int i = 0;

    map = NULL;
    fd = 0;
	if (argc == 2 && argv[1])
	{
        fd = open(argv[1], O_RDONLY);
        if (fd == -1)
            exit_with_err(collector, OPEN);
        check_errs(collector, argc, argv);
        check_dups(collector, map, argv, player);
        i = get_elements(collector, argv, player);
        printf("%d\n", i);
        map = get_map(collector, argc, argv, i);
        check_map(collector, map);  
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
