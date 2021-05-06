/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrinova <lkrinova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:51:08 by lkrinova          #+#    #+#             */
/*   Updated: 2021/04/11 07:23:27 by lkrinova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include "libft/libft.h"
# include "minilibx_opengl/mlx.h"
# define M_SCALE 16
# define WKEY 13
# define SKEY 1
# define AKEY 0
# define DKEY 2
# define LARROW 123
# define RARROW 124
# define FOV (M_PI/3)
# define ESCAP 53

typedef struct s_fxy
{
	double 		x;
	double 		y;
}				t_fxy;

typedef struct s_xy
{
	double 		x;
	double 		y;
}				t_xy;

typedef struct  s_img {
	void        *im;
	int 		size_x;
	int 		size_y;
	char        *addr;
}               t_img;

typedef struct  s_vars {
	void        *ml_p;
	void        *w_p;
	t_img 		img;
}               t_vars;

typedef struct s_player
{
	t_fxy 		pos;
	double 		pov;
	t_fxy		ray;
    double		r_st;
    double 		r_end;

}				t_player;

typedef struct s_rays
{
    double 		dist;
	t_xy 		r_pos;
    double 		size;
	double 		hitx;
	double 		hity;
	int         qdrnt;
}				t_rays;

typedef struct s_textur
{
	char 		*ig;
	int	    	wid;
	int 		hei;
	char 		*addr;
	int			bpp;
	int			sz_l;
	int			end;
}				t_textur;

typedef struct 	s_map
{
	t_xy 		size;
	char		**map_ar;
	int 		m_start;
	t_player	plr;
	t_textur 	we;
	t_textur 	no;
	t_textur 	so;
	t_textur 	ea;
	t_textur 	sprite;
}				t_map;



typedef struct s_cub
{
	t_xy 		res;
	char 		*no_tex;
	char 		*so_tex;
	char 		*ea_tex;
	char 		*we_tex;
	char 		*sprite;
	int 		floor_rgb;
	int			ceil_col;
	double 		dist_plane;
	t_map 		m;
	t_rays 		*rs;
	t_vars 		ml;
}				t_cub;



char 	*check_map_f(char *str);
int 	bad_sosed(char **arr, int i, int j);
void 	find_player(char **ar, t_cub *flags);
void	parse(char *buffer, t_cub *flags);
void 	get_param(char **arr, t_cub *flags);
void 	get_map(char **arr, t_cub *flags);
void 	free_mass(char **mass);
void	get_r_rgb(char *s, t_cub *flags);
int		check_rgb(char *s);
int 	is_valid(char **ar);
void 	draw_sqaure(int x, int y, t_img img, int color);
void    pixel_put(t_img *img, int x, int y, unsigned int color);
unsigned int pixel_get(t_textur *textura, int x, int y);
void 	draw_map(t_cub flags);
void 	draw_player(int x, int y, t_img img, int color);
void	draw_col(t_cub *fl, t_textur *tx, int c_n);
int		move(int keycode, t_cub *fl);
void	clean_s(t_cub flags);
int		render(t_cub *fl);
float	get_pov(char c);
void	get_texture(char *str, t_cub *flagg);
void draw_texture(t_cub *fl);
void	get_text(t_cub *fl);
void 	cast_view(t_player *pl, t_cub *fl);
void	rays_arr_init(t_cub *flags);
int     f_quadrant(double angle);
double is_wall(t_cub *fl, double x, double y);

#endif
