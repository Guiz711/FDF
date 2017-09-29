/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 10:10:53 by gmichaud          #+#    #+#             */
/*   Updated: 2017/09/29 18:24:23 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include "libft.h"
# include "libmlxext.h"

# define REND_WIDTH 1500
# define MENU_WIDTH 400
# define WIN_WIDTH MENU_WIDTH + REND_WIDTH
# define WIN_HEIGHT 1000

# define COLOR_DEPTH 32
# define ENDIAN 1

# define KEYPRESSMASK (1L<<0)
# define KEYPRESS 2

typedef struct	s_env
{
	void		*init;
	void		*win;
	int			z_pitch;
	int			r_pitch;
	int			draw_mode;
	int			proj_mode;
	int			proj_scale;
	int			z_scale;
}				t_env;

typedef	struct	s_map
{
	t_vbuffer	*vlst;
	t_poly_lst	*tiles;
	t_mtx4		model;
	t_mtx4		world;
	t_mtx4		view;
	int			height;
	int			width;
}				t_map;

typedef struct	s_args
{
	t_env		*env;
	t_map		*map;
}				t_args;

/*
** error functions
*/

int				error_mlx(void);
int				error_win(void);
void			error_map(t_args *args);
void			error_display(t_args *args);

/*
** map creation functions
*/

int				init_params(t_args *args, char *map_file);
int				fill_map(t_map *map, char **point_list);
t_poly_lst		*create_polys(int w, int h);

/*
** window drawing functions
*/

int				win_draw(void *args);
int				update_img(t_args *args);
int				put_params(t_env *env);

/*
** keyboard management functions
*/

int				keypress(int keycode, void *args);
int				rot_keys(int keycode, t_args *args);

/*
** other functions
*/

void			quit(t_args *args);
void			update_map(t_map *map, t_mtx4 mtx);

#endif
