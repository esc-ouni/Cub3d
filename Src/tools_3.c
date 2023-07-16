/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:54:44 by idouni            #+#    #+#             */
/*   Updated: 2023/07/16 16:47:48 by idouni           ###   ########.fr       */
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

void    check_dups(t_player *player, char **map, char const *argv[])
{
    (void)map;
    (void)player;
    (void)argv;
    // char *str = NULL;
    // int s = 0;
    // int n = 0;
    // int w = 0;
    // int e = 0;
    // int fd;

    // fd = open(argv[1], O_RDONLY);
    // if (fd == -1)
    //     exit_with_err(player->vars->collector, OPEN);
    // while((str = get_next_line(fd)))
    // {
    //     if (!ft_strncmp(ft_msplit(player->vars, str, ' ', TMP)[0], "NO", 2))
    //         n++;
    //     else if (!ft_strncmp(ft_msplit(player->vars, str, ' ', TMP)[0], "SO", 2))
    //         s++;
    //     else if (!ft_strncmp(ft_msplit(player->vars, str, ' ', TMP)[0], "WE", 2))
    //         w++;
    //     else if (!ft_strncmp(ft_msplit(player->vars, str, ' ', TMP)[0], "EA", 2))
    //         e++;
    //     // free(str);
    //     // str = NULL;
    // }
    // if (n != 1 || e != 1 || w != 1 || s != 1)
    //     exit_with_err(player->vars->collector, PARSE);
}

void    check_errs(t_player *player, int argc, char const *argv[])
{
    (void)argc;
    if(ft_strlen(strstr(argv[1], ".cub")) != 4)
        exit_with_err(player->vars->collector, PARSE);
}

int     point_surronded(t_player *player, char **map, int y, int x)
{
    int x_m = 0;
    int y_m = 0;

    while (map[y_m])
        y_m++;
    
    x_m = ft_strlen(map[y]);

    if ((x - 1) < 0 || (x + 1) > x_m)
        exit_with_err(player->vars->collector, PARSE);

    if (map[y][x-1] == ' ' || map[y][x+1] == ' ')    
        exit_with_err(player->vars->collector, PARSE);

    if ((y - 1) < 0 || (y + 1) > y_m)
        exit_with_err(player->vars->collector, PARSE);

    if (x >= ft_strlen(map[y-1]) || x >= ft_strlen(map[y+1]))
        exit_with_err(player->vars->collector, PARSE);

    if (map[y-1][x] == ' ' || map[y+1][x] == ' ')    
        exit_with_err(player->vars->collector, PARSE);
    return (1);
}

void    check_mapa(t_player *player, char **map)
{
    int y = 0;
    int x = 0;



    //check middle
    while(map[y])
    {
        if ((map[y][0] != '1' && map[y][0] != ' ') || (map[y][ft_strlen(map[y]) - 1] != '1' && map[y][ft_strlen(map[y]) - 1] != ' '))
            exit_with_err(player->vars->collector, PARSE);
        y++;
    }
    //check upper
    y = 0;
    x = 0;
    while(map[y][x])
    {
        if (map[y][x] != '1' && map[y][x] != ' ')
            exit_with_err(player->vars->collector, PARSE);
        x++;
    }
    //check bottom
    while (map[y])
        y++;
    y--;
    x = 0;
    while(map[y][x])
    {
        if (map[y][x] != '1' && map[y][x] != ' ')
            exit_with_err(player->vars->collector, PARSE);
        x++;
    }
}

void    check_mapb(t_player *player, char **map)
{
    int y = 0;
    int x = 0;
    int c = 0;
    float p_y = 0;
    float p_x = 0;

    while (map[y])
    {
        while(map[y][x])
        {
            if (map[y][x] == 'N' || map[y][x] == 'E' || map[y][x] == 'W' || map[y][x] == 'S')
            {
                p_x = (float)(x * BLOCK);
                p_y = (float)(y * BLOCK);
                c++;
            }
            else if (map[y][x] != '0' && map[y][x] != '1' && map[y][x] != ' ')
                exit_with_err(player->vars->collector, PARSE);
            x++;
        }
        y++;
        x = 0;
    }
    if (c != 1)
        exit_with_err(player->vars->collector, PARSE);
    player->p_x = p_x + BLOCK/2;
	player->p_y = p_y + BLOCK/2;
}

void    check_map(t_player *player, char **map)
{
    int y = 0;
    int x = 0;

    check_mapa(player, map);
    check_mapb(player, map);
    while (map[y])
    {
        while(map[y][x])
        {
            if (map[y][x] == '0')
                point_surronded(player, map, y, x);
            else if ((map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E' || map[y][x] == 'W'))
                point_surronded(player, map, y, x);
            x++;  
        }
        y++;
        x = 0;
    }
}

char **get_map(t_player *player, int argc, char const *argv[], int t)
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
    map = h_malloc(player->vars->collector, (count_alloc_size(player->vars->collector, argv, fd) * sizeof(char *)), map, NTMP);
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        exit_with_err(player->vars->collector, OPEN);
    while((s = get_next_line(fd))) //not appopriate
    {
        if(i == t)
            itsmap = 1;
        if (itsmap)
        {
            map[i2] = ft_mstrdup(player->vars->collector, s, NTMP);
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

int     get_elem(t_player *player, char const *argv[])
{
    char *s;
    int fd;
    int i = 0;;

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        exit_with_err(player->vars->collector, OPEN);
    while((s = get_next_line(fd))) //not appopriate
    {
        if (strnstr(s, "NO", 2))
            player->vars->up_c = ft_mstrdup(player->vars->collector, s+3, TMP);
        else if (strnstr(s, "SO", 2))
            player->vars->dn_c = ft_mstrdup(player->vars->collector, s+3, TMP);
        else if (strnstr(s, "WE", 2))
            player->vars->rg_c = ft_mstrdup(player->vars->collector, s+3, TMP);
        else if (strnstr(s, "EA", 2))
            player->vars->lf_c = ft_mstrdup(player->vars->collector, s+3, TMP);
        else if (strnstr(s, "F", 1))
            player->vars->f_color = extract_color(player, s+1);
        else if (strnstr(s, "C", 1))
            player->vars->c_color = extract_color(player, s+1);
        else if (strnstr(s, "1", ft_strlen(s)))
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

int    get_elements(t_player *player, char const *argv[])
{
    int i = 0;
    // int fd;

    // fd = open(argv[1], O_RDONLY);
    // if (fd == -1)
    //     exit_with_err(collector, OPEN);

    i = get_elem(player, argv);
    
	player->vars->up = new_image_from_xpm(player, player->vars->up_c);
	player->vars->dn = new_image_from_xpm(player, player->vars->dn_c);
	player->vars->lf = new_image_from_xpm(player, player->vars->lf_c);
	player->vars->rg = new_image_from_xpm(player, player->vars->rg_c);
    return (i);
}

char **parse_file(t_player *player, int argc, char const *argv[])
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
            exit_with_err(player->vars->collector, OPEN);
        check_errs(player, argc, argv);
        check_dups(player, map, argv);
        i = get_elements(player, argv);
        map = get_map(player, argc, argv, i);
        check_map(player, map); 
        return (map);
	}
    exit_with_err(player->vars->collector, ARGS);
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
