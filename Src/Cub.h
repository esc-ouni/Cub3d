/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:54:30 by idouni            #+#    #+#             */
/*   Updated: 2023/07/22 16:41:54 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <time.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <math.h>
# include <mlx.h>
// # include "../../minilibx-linux/mlx.h"
# include <fcntl.h>
# include "../Get_next_line/get_next_line.h"
# include "../LIBF/libft.h"


# define HORZ_U 15
# define HORZ_D 16
# define VERT_L 17
# define VERT_R 27


# define NORTH 90
# define EAST  0
# define SOUTH 270
# define WEST  180


# define WIDTH 2000
# define HEIGHT 1000
# define BLOCK 1000

# define MV_SP (BLOCK / 5)
# define R_AN  3

# define M_BLOCK 8

# define TRANS 0xFF000000

# define C_COLOR 0x00191970
# define F_COLOR 0x002e3134

# define GREY 0x005A5A5A
# define L_GREY 0x00d3d3d3

# define M_BLACK 0x88000000
# define M_WHITE 0x88FFFFFF

# define BLACK 0x00000000
# define WHITE 0x00FFFFFF

# define GREEN 0x00008000
# define V_GREEN 0x009FE2BF
# define V_WHITE 0x006C705D
# define BLUE 0x00030DFF
# define RED 0x00FF0D03

# define ESC         53

# define SP        49

# define M_UP        13
# define M_DN        1
# define M_LF        0
# define M_RG        2

# define K_UP        126
# define K_DN        125
# define K_R         124
# define K_L         123

# if (WIDTH > 2560) || (HEIGHT > 1396)
	# undef	WIDTH
	# undef	HEIGHT
	# define	WIDTH	2560
	# define	HEIGHT	1396
# endif

typedef enum e_flag
{
	MALLOC,
	PARSE,
	NTMP,
	ARGS,
	OPEN,
	MAP,
	TMP,
	ALL,
	MLX,
	COS,
	SIN,
	TAN
}	t_flag;

typedef struct s_ntmp
{
	void			*ntmp_addr;
	struct s_ntmp	*next;
}	t_ntmp;

typedef struct s_tmp
{
	void			*tmp_addr;
	struct s_tmp	*next;
}	t_tmp;

typedef struct s_collector
{
	t_tmp				*tmp_cltr;
	t_ntmp				*ntmp_cltr;
}	t_collector;

typedef struct s_vector
{
	float	x;
	float	y;
}	t_vector;

typedef struct s_data
{
	void	*img_ptr;
	char	*img_addr;
	int		byte_pixel;
	int		size_line;
	int		endian;
}		t_data;

typedef struct s_vars
{
	void			*mlx;
	void			*win;
	char			**map;
	int				map_h;
	int				map_w;
	int				c_color;
	int				f_color;
	char			*up_c;
	char			*dn_c;
	char			*lf_c;
	char			*rg_c;
	t_data			*up;
	t_data			*dn;
	t_data			*lf;
	t_data			*rg;
	t_data			*fix_img;
	t_data			*m_fix_img;
	t_collector		**collector;
}	t_vars;

typedef struct s_ray
{
	float		dx;
	float		dy;
	float		length;
	float		angle;
	float		t1;
	float		t2;
	float		v_d_inter;
	float		h_d_inter;
	int			side;
	int			tex_x;
	float		c;
}		t_ray;

typedef struct s_player
{
	int			w;
	int			d;
	int			rl;
	int			xf;
	int			yf;
	float		p_x;
	float		p_y;
	int			m;
	float		angle;
	float		t_angle;
	float		f_angle;
	float		factor;
	int			color;
	void		**p;
	t_vector	*vec2;
	t_vector	*vec1;
	t_ray		*ray;
	t_vars		*vars;
}		t_player;

int			hokking(t_player *player);
void		update_params(t_player *player);


char		**ft_msplit(t_vars *vars, char const *s, char const c, t_flag flag);
char		*ft_mstrdup(t_collector **collector, const char *s1, t_flag flag);
char		*ft_mstrtrim(t_vars *vars, char const *s1, char const *set, t_flag flag);
char		*ft_msubstr(t_vars *vars, char const *s, unsigned int start, size_t len);

int			wall_hit_hup(t_player *player, int x, int y);
int			wall_hit_hdn(t_player *player, int x, int y);
int			wall_hit_vrg(t_player *player, int x, int y);
int			wall_hit_vlf(t_player *player, int x, int y);

void		update_params(t_player *player);
int			ft_atoi(t_collector **collector, const char *str);
void		update_degree(t_player *player, float  deg_angle);
void		destroy_prev_imges(t_player *player);
void		destroy_fix_imges(t_player *player);
int			darkenColor(int color, int amount);
float		ft_pow(float n);
void		draw_point(t_player *player, t_data *img, int x, int y, int color);
float		ft_abs(float n);
float		trigo(float angle, t_flag flag);
float		rad_to_deg(float angle);
float		up_degree(float angle, float add_angle);
float		deg_to_rad(float angle);
t_player	*init(int argc, char const *argv[]);
int			count_alloc_size(t_collector **collector, char const *argv[], int fd);
int			handlerp(int key, t_player *player);
int			handlerr(int key, t_player *player);
void		update_scene(t_player *player);
t_data		*draw_2d_map(t_player *player);
void		rotate_vector(t_vector *direction, float  angle);
int			mouse_movement(int x, int y, t_player *player);
void		exit_with_err(t_collector **collector, t_flag cause);
t_data		*ft_transparency(t_player *player, t_data *p_img, int width, int height);
t_vector	*find_horizontal_iterset(t_player *player, t_ray *ray, t_vector *vector);
t_vector	*find_vertical_iterset(t_player *player, t_ray *ray, t_vector *vector);
void		check_collision(t_player *player, float  x, float  y);
t_ray		*cast_rays(t_player *player, t_data *p_img, t_ray *ray);
float		draw_ray(t_player *player, t_data *p_img, int color, t_ray *ray);
void		updateAndRenderScene(t_player *player);
t_data		*new_image_from_xpm(t_player *player, char *file_dstination);
t_data		*draw_cf(t_player *player);
void		debug(void);
int			ft_ext(t_player *player);
t_data		*new_image(t_vars *vars, int width, int height, t_flag type);
void		free_tmp(t_collector **collector);
void		free_ntmp(t_collector **collector);
void		head_alloc(t_collector **collector);
void		tmp_alloc(t_collector **collector, size_t s, void **p);
void		my_mlx_pixel_put(t_player *player, t_data *data, int x, int y, int color);
void		ft_collectorclear(t_collector **collector, t_flag flag);
void		ntmp_alloc(t_collector **collector, size_t s, void **p);
void		*h_malloc(t_collector **collector, size_t s, void *p, t_flag flag);
char		**parse_file(t_player *player, int argc, char const *argv[]);
t_data		*draw_player(t_player *player, t_data *p_img);

void		draw_line(t_player *player, t_data *p_img, int color, int x2, int y2);

# endif
