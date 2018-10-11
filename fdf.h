/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 19:54:12 by cgleason          #+#    #+#             */
/*   Updated: 2018/09/23 22:24:44 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "minilibx_macos/mlx.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>

# define MIN(x1, x2) (((x1) < (x2)) ? x1 : x2)
# define MAX(x1, x2) (((x1) < (x2)) ? x2 : x1)

# define PI M_PI
# define C1 0x0034675C
# define C2 0x00B7B8B6

# define THETA_0 (PI / 3)
# define PHI_0 (PI / 6)
# define D_0 2.0
# define STRETCH_0 (1.0 / 4)

# define CLICKED (1 << 0)
# define ZOOM (1 << 1)
# define STRETCH (1 << 2)
# define HROTATE (1 << 3)
# define VROTATE (1 << 4)
# define HROTATEB (1 << 5)
# define VROTATEB (1 << 6)

# define HRSPEED 0.05
# define VRSPEED 0.02

# define CAM2SCREEN 2.0

# define ENDIND(e) (e ? bytespp - i : i)

typedef int				t_pt3d[3];

typedef int				t_pt2d[2];

typedef unsigned int	t_upt2d[2];

typedef double			t_fpt3d[3];

typedef double			t_fpt2d[2];

typedef struct	s_imgdata
{
	void	*mlx_ptr;
	void	*img_ptr;
	char	*img_loc;
	int		width;
	int		height;
	int		bpp;
	int		sl;
	int		ndn;
}				t_imgdata;

typedef struct	s_base
{
	double	boffset;
	double	bstretch;
	t_fpt2d	bcenter;
	t_pt2d	start;
}				t_base;

typedef struct	s_map
{
	t_byte		flags;
	int			**coords;
	int			width;
	int			height;
	int			min;
	int			max;
	void		*mlx_ptr;
	void		*win_ptr;
	double		theta;
	double		phi;
	double		offset;
	t_fpt2d		center;
	double		stretch;
	t_base		base;
	t_imgdata	img;
}				t_map;

typedef void	(*t_ip)(t_pt2d, t_pt2d, t_map *, t_upt2d);

double			confine_double(double x, double lbound, double rbound);
int				ct_words(char *s);
void			free_matrix(void ***twod);

int				handle_key_press(int key, void *param);
int				handle_key_release(int key, void *param);
int				flip_on_click(int button, int x, int y, void *param);
int				flip_off_click(int button, int x, int y, void *param);
int				move_mouse(int x, int y, void *param);
void			back2basics(t_map *mapp);
void			close_window(t_map *mapp);
int				clean_exit(void *param);
void			set_hooks(void *win_ptr, void *param);
int				refresh_window(void *param);

void			ip00(t_pt2d p1, t_pt2d p2, t_map *mapp, t_upt2d color);
void			ip01(t_pt2d p1, t_pt2d p2, t_map *mapp, t_upt2d color);
void			ip10(t_pt2d p1, t_pt2d p2, t_map *mapp, t_upt2d color);
void			ip11(t_pt2d p1, t_pt2d p2, t_map *mapp, t_upt2d color);

void			place_coords(t_map *mapp);
void			project(t_fpt3d sp, t_pt2d dp, t_map *mapp);
void			place_line(t_fpt3d fp1, t_fpt3d fp2, t_map *mapp);
void			add_to_image(t_pt3d p1, t_pt3d p2, t_map *mapp);

unsigned int	color_blend(unsigned int c1, unsigned int c2, double ratio);
void			ft_color_pixel(int x, int y, t_imgdata *img, unsigned int rgb);

void			close_window(t_map *mapp);

#endif
