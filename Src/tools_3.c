/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:54:44 by idouni            #+#    #+#             */
/*   Updated: 2023/07/23 12:33:41 by idouni           ###   ########.fr       */
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
        write (2, "\033[0;32mError\nNOT_A_VALID_ARGS_NUMBER\033[0;37m\n", 45);
    else if (cause == MLX)
		write (2, "\033[0;32mError\nMLX_FAILED\033[0;37m\n", 32);
    else if (cause == OPEN)
		write (2, "\033[0;32mError\nUNABLE_TO_OPEN_A_FILE\033[0;37m\n", 43);
    else if (cause == MAP)
		write (2, "\033[0;32mError\nINCOMPATIBLE_SIZE\033[0;37m\n", 39);
    ft_collectorclear(collector, ALL);
    exit (1);
}

void duppp(t_player *player, int fd, t_varr  *varr, char *str)
{
    while((str = get_next_line(fd)))
    {
        varr->first_part = ft_msplit(player->vars, str, ' ', TMP)[0];
        if (varr->first_part && !ft_strncmp(varr->first_part, "NO", ft_strlen(varr->first_part)))
            (varr->n)++;
        else if (varr->first_part && !ft_strncmp(varr->first_part, "SO", ft_strlen(varr->first_part)))
            (varr->s)++;
        else if (varr->first_part && !ft_strncmp(varr->first_part, "WE", ft_strlen(varr->first_part)))
            (varr->w)++;
        else if (varr->first_part && !ft_strncmp(varr->first_part, "EA", ft_strlen(varr->first_part)))
            (varr->e)++;
        else if (varr->first_part && !ft_strncmp(varr->first_part, "F", ft_strlen(varr->first_part)))
            (varr->f)++;
        else if (varr->first_part && !ft_strncmp(varr->first_part, "C", ft_strlen(varr->first_part)))
            (varr->c)++;
        else if (varr->first_part && !ft_strnstr(str, "1", ft_strlen(str)) && !ft_strnstr(str, "0", ft_strlen(str)))
			(varr->k)++;
        free(str);
    }
	if (varr->k)
		exit_with_err(player->vars->collector, PARSE);
}

void    check_dups(t_player *player, char const *argv[])
{
	t_varr  *varr;
    char 	*str;
    int 	fd;

	str = NULL;
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        exit_with_err(player->vars->collector, OPEN);
	varr = NULL;
	varr = h_malloc(player->vars->collector, sizeof(t_varr), varr, TMP);
	varr->c = 0;
	varr->f = 0;
	varr->n = 0;
	varr->s = 0;
	varr->e = 0;
	varr->w = 0;
	varr->k = 0;
    varr->first_part = NULL;
	duppp(player, fd, varr, str);
    if (varr->n != 1 || varr->e != 1 || varr->w != 1 || varr->s != 1 || varr->f != 1 || varr->c != 1)
        exit_with_err(player->vars->collector, PARSE);
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

void void_check_middle(t_player *player, char **map)
{
    int y;
    int x;

    y = 0;
    x = 0;
    while(map[y])
    {
        if ((map[y][0] != '1' && map[y][0] != ' ') || (map[y][ft_strlen(map[y]) - 1] != '1' && map[y][ft_strlen(map[y]) - 1] != ' '))
            exit_with_err(player->vars->collector, PARSE);
        y++;
    }
}

void    check_mapa(t_player *player, char **map)
{
    int y;
    int x;

    y = 0;
    x = 0;
    void_check_middle(player, map);
    while(map[y][x])
    {
        if (map[y][x] != '1' && map[y][x] != ' ')
            exit_with_err(player->vars->collector, PARSE);
        x++;
    }
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

void	check_mapb_t(t_player *player, char **map, int *chr, int *c)
{
    int y;
    int x;
	
	y = 0;
    x = 0;
    while (map[y])
    {
        while(map[y][x])
        {
            if (map[y][x] == 'N' || map[y][x] == 'E' || map[y][x] == 'W' || map[y][x] == 'S')
            {
                player->p_x = (float )(x * BLOCK) + BLOCK/2;
                player->p_y = (float )(y * BLOCK) + BLOCK/2;
                (*chr) = map[y][x];
                (*c)++;
            }
            else if (map[y][x] != '0' && map[y][x] != '1' && map[y][x] != ' ')
                exit_with_err(player->vars->collector, PARSE);
            x++;
        }
        y++;
        x = 0;
    }
}


void    check_mapb(t_player *player, char **map)
{

    int c;
    int chr;

    chr = 0;
    c = 0;

	check_mapb_t(player, map, &chr, &c);
    if (c != 1)
        exit_with_err(player->vars->collector, PARSE);
    if (chr == 'N')
	    player->angle = 3 * (M_PI/2);
    else if (chr == 'E')
	    player->angle = 0;
    else if (chr == 'S')
	    player->angle = M_PI/2;
    else if (chr == 'W')
	    player->angle = M_PI;
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

char    **get_map_cont(t_player *player, int fd, int t, char **map)
{
    int     itsmap;
	int     i2;
	int     i;
	char    *s;

	i = 0;
	i2 = 0;
	s = NULL;
    itsmap = 0;
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

char **get_map(t_player *player, char const *argv[], int t)
{
	int	    fd;
	char    **map;

	fd = 0;
	map = NULL;  
    map = h_malloc(player->vars->collector, (count_alloc_size(player->vars->collector, argv, fd) * sizeof(char *)), map, NTMP);
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        exit_with_err(player->vars->collector, OPEN);

	return (get_map_cont(player, fd, t, map));	
}

void    check_vergs(t_player *player, char *s)
{
    if (!ft_strchr(s, ','))
        exit_with_err(player->vars->collector, PARSE);
    else if (ft_strchr(ft_strchr(ft_strchr(s, ',')+1, ',')+1, ','))
        exit_with_err(player->vars->collector, PARSE);
    else if (ft_strchr(ft_strchr(s, ',')+1, ','))
        return ;
    else
        exit_with_err(player->vars->collector, PARSE);
}

int extract_color(t_player *player, char *color)
{
    int i = 0;
    char **s;
    int color_c;

    color_c = 0;
    color = ft_mstrtrim(player->vars, color, " ", TMP);
    check_vergs(player, color);
    s = ft_msplit(player->vars, color, ',', TMP);
    while (s[i])
        i++;
    if (i != 3)
        exit_with_err(player->vars->collector, PARSE);
    color_c = ft_atoi(player->vars->collector, ft_mstrtrim(player->vars, *s, " ", TMP));
    color_c <<= 8;
    s++;
    color_c |= ft_atoi(player->vars->collector, ft_mstrtrim(player->vars, *s, " ", TMP));
    color_c <<= 8;
    s++;
    color_c |= ft_atoi(player->vars->collector, ft_mstrtrim(player->vars, *s, " ", TMP));
    return (color_c);
}

int get_map_indx(t_player *player, int fd, int i, char *s)
{
    while((s = get_next_line(fd)))
    {
        if (ft_strnstr(s, "NO", 2))
            player->vars->up_c = ft_mstrdup(player->vars->collector, ft_mstrtrim(player->vars, s+2, " ", TMP), TMP);
        else if (ft_strnstr(s, "SO", 2))
            player->vars->dn_c = ft_mstrdup(player->vars->collector, ft_mstrtrim(player->vars, s+2, " ", TMP), TMP);
        else if (ft_strnstr(s, "WE", 2))
            player->vars->rg_c = ft_mstrdup(player->vars->collector, ft_mstrtrim(player->vars, s+2, " ", TMP), TMP);
        else if (ft_strnstr(s, "EA", 2))
            player->vars->lf_c = ft_mstrdup(player->vars->collector, ft_mstrtrim(player->vars, s+2, " ", TMP), TMP);
        else if (ft_strnstr(s, "F", 1))
            player->vars->f_color = extract_color(player, ft_mstrtrim(player->vars, s+1, " ", TMP));
        else if (ft_strnstr(s, "C", 1))
            player->vars->c_color = extract_color(player, ft_mstrtrim(player->vars, s+1, " ", TMP));
        else if (ft_strnstr(s, "1", ft_strlen(s)))
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

int     get_elem(t_player *player, char const *argv[])
{
    char *s;
    int fd;
    int i;
    
	s = NULL;
	i = 0;
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        exit_with_err(player->vars->collector, OPEN);
	i = get_map_indx(player, fd, i, s);
    return (i);
}

void    check_xpm_size(t_player *player, char *file_dstination)
{
    char **sp = NULL;
    char *s = NULL;
    int fd = 0;

    fd = open(file_dstination, O_RDONLY);
    if (fd == -1)
        exit_with_err(player->vars->collector, OPEN);
    while ((s = get_next_line(fd)))
    {
        if (ft_strnstr(s, "\"",1))
        {
            sp = ft_msplit(player->vars, s+1, ' ', TMP);
            free(s);
            break;
        }
        free(s);
        s = NULL;
    }
    if (!strcmp(sp[0], "1000") && !strcmp(sp[1], "1000"))
        return ;
    else
		exit_with_err(player->vars->collector, MAP);
}

int    get_elements(t_player *player, char const *argv[])
{
    int i;
    
    i = 0;
    i = get_elem(player, argv);
	player->vars->up = new_image_from_xpm(player, player->vars->up_c);
    check_xpm_size(player, player->vars->up_c);
	player->vars->dn = new_image_from_xpm(player, player->vars->dn_c);
    check_xpm_size(player, player->vars->dn_c);
	player->vars->lf = new_image_from_xpm(player, player->vars->lf_c);
    check_xpm_size(player, player->vars->lf_c);
	player->vars->rg = new_image_from_xpm(player, player->vars->rg_c);
    check_xpm_size(player, player->vars->rg_c);
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
        check_dups(player, argv);
        i = get_elements(player, argv);
        map = get_map(player, argv, i);
        check_map(player, map); 
        return (map);
	}
    exit_with_err(player->vars->collector, ARGS);
    return (NULL);
}

float    trigo(float  angle, t_flag flag)
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
