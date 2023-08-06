/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:54:30 by idouni            #+#    #+#             */
/*   Updated: 2023/08/06 09:09:29 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <mlx.h>
# include <fcntl.h>
# include "../g_n_l/get_next_line.h"
# include "../libft/libft.h"

# define NORTH 15
# define SOUTH 16
# define WEST 17
# define EAST 27

# define WIDTH 1800
# define HEIGHT 900

# define R_AN  3

# define M_B 8

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

typedef enum e_flag
{
	MALLOC,
	PARSE,
	NTMP,
	ARGS,
	NONE,
	OPEN,
	XPM,
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

typedef struct s_varr
{
	int		s;
	int		n;
	int		w;
	int		e;
	int		c;
	int		f;
	int		k;
	char	*fp;
}	t_varr;

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
	int				m_h;
	int				m_w;
	int				c_color;
	int				f_color;
	char			*no_c;
	char			*we_c;
	char			*so_c;
	char			*ea_c;
	t_data			*no;
	t_data			*we;
	t_data			*so;
	t_data			*ea;
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
	float		v_d;
	float		h_d;
	int			side;
	int			tex_x;
	int			tex_y;
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
	int			last_pos;
	int			b_p;
	int			mv_sp;
	float		mx;
	float		my;
	float		p_mx;
	float		p_my;
	float		angle;
	float		t_angle;
	float		f_angle;
	float		factor;
	int			color;
	int			width;
	int			height;
	int			block;
	void		**p;
	t_vector	*v2;
	t_vector	*v1;
	t_ray		*ray;
	t_vars		*v;
	t_data		*t_img;
}		t_player;

void		destruct(t_player *r_p);
void		check_paths(t_player *plyr);
int			m_hookr(int keycode, int x, int y, t_player *plyr);
int			m_hookp(int keycode, int x, int y, t_player *plyr);
void		check_existence(t_player *plyr, char *file_dstination);
void		get_elements(t_player *plyr);
t_data		*creat_tmap(t_player *plyr);
void		resizer(t_player *player);
void		check_map(t_player *plyr, char **map);
char		**get_map(t_player *plyr, char const *argv[], int t);
void		check_dups(t_player *plyr, char const *argv[]);
void		check_errs(t_player *plyr, char const *argv[]);
int			get_map_indx(t_player *plyr, int fd, int i, char *s);
int			point_surronded(t_player *plyr, char **map, int y, int x);
t_vector	*h_up_iterset(t_player *plyr, t_ray *ray, t_vector *vector);
t_vector	*h_dn_iterset(t_player *plyr, t_ray *ray, t_vector *vector);
void		draw_3d_map(t_player *plyr, t_data *p_img, t_ray *ray);
void		draw_wall_part(t_player *plyr, t_data *p_img, t_ray ray, \
int x_index);
int			hokking(t_player *plyr);
void		update_params(t_player *plyr);

char		**ft_msplit(t_vars *vars, char const *s, char const c, t_flag flag);
char		*ft_mstrdup(t_collector **collector, const char *s1, t_flag flag);
char		*ft_mstrtrim(t_vars *vars, char const *s1, char const *set, \
t_flag flag);
char		*ft_msubstr(t_vars *vars, char const *s, unsigned int start, \
size_t len);

int			wall_hit_hup(t_player *plyr, int x, int y);
int			wall_hit_hdn(t_player *plyr, int x, int y);
int			wall_hit_vrg(t_player *plyr, int x, int y);
int			wall_hit_vlf(t_player *plyr, int x, int y);

void		felina(int fd, char *str);
void		update_params(t_player *plyr);
int			ft_atoi(t_player *plyr, const char *str);
void		update_degree(t_player *plyr, float deg_angle);
void		destroy_prev_imges(t_player *plyr);
void		destroy_fix_imges(t_player *plyr);
int			darken_color(int color, int amount);
float		ft_pow(float n);
float		ft_abs(float n);
float		trigo(float angle, t_flag flag);
float		rad_to_deg(float angle);
float		up_degree(float angle, float add_angle);
float		deg_to_rad(float angle);
t_player	*init(int argc, char const *argv[]);
int			count_alloc_size(t_player *plyr, char const *argv[], int fd);
int			handlerp(int key, t_player *plyr);
int			handlerr(int key, t_player *plyr);
void		update_scene(t_player *plyr);
t_data		*draw_2d_map(t_player *plyr);
void		rotate_vector(t_vector *direction, float angle);
int			mouse_movement(int x, int y, t_player *plyr);
void		exit_with_err(t_player *plyr, t_flag cause);
t_data		*ft_transparency(t_player *plyr, t_data *p_img, int \
width, int height);
t_vector	*find_horizontal_iterset(t_player *plyr, \
t_ray *ray, t_vector *vector);
t_vector	*find_vertical_iterset(t_player *plyr, t_ray *ray, \
t_vector *vector);
void		check_collision(t_player *plyr, float x, float y);
t_ray		*cast_rays(t_player *plyr, t_ray *ray);
float		draw_ray(t_player *plyr, t_ray *ray);
void		update_params(t_player *plyr);
void		xpm_failed(t_player *plyr);
t_data		*new_image_from_xpm(t_player *plyr, char *file_dstination);
t_data		*draw_cf(t_player *plyr);
int			ft_ext(t_player *plyr);
t_data		*new_image(t_player *plyr, int width, int height, t_flag type);
void		free_tmp(t_collector **collector);
void		free_ntmp(t_collector **collector);
void		head_alloc(t_collector **collector);
void		tmp_alloc(t_collector **collector, size_t s, void **p);
void		ft_collectorclear(t_collector **collector, t_flag flag);
void		check_xpm_size(t_player *plyr, char *file_dstination);
void		ntmp_alloc(t_collector **collector, size_t s, void **p);
void		*h_malloc(t_collector **collector, size_t s, void *p, t_flag flag);
char		**parse_file(t_player *plyr, int argc, char const *argv[]);
t_data		*draw_player(t_player *plyr, t_data *p_img);
void		draw_point(t_player *plyr, int x, int y, int color);
void		my_mlx_pixel_put(t_player *plyr, int x, int y, int color);
void		draw_line(t_player *plyr, int color, int x2, int y2);

#endif
