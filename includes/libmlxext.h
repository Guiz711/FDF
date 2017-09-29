/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmlxext.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 10:10:53 by gmichaud          #+#    #+#             */
/*   Updated: 2017/09/29 17:18:13 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMLXEXT_H
# define LIBMLXEXT_H

# include <math.h>
# include <stdlib.h>
# include "libft.h"

typedef struct	s_mtx4
{
	float		a[4];
	float		b[4];
	float		c[4];
	float		d[4];
}				t_mtx4;

typedef struct	s_vec2
{
	float		x;
	float		y;
}				t_vec2;

typedef struct	s_vec3
{
	float		x;
	float		y;
	float		z;
}				t_vec3;

typedef struct	s_vec4
{
	float		x;
	float		y;
	float		z;
	float		w;
}				t_vec4;

typedef struct	s_vtx
{
	t_vec4		pos;
	float		elev;
}				t_vtx;

typedef	struct	s_vbuffer
{
	t_vtx		*data;
	t_vtx		*cache;
	int			size;
}				t_vbuffer;

typedef struct	s_poly_lst
{
	int			*data;
	int			p_size;
	int			p_cnt;
}				t_poly_lst;

typedef struct	s_img
{
	void		*ptr;
	int			color_depth;
	int			width;
	int			height;
	int			endian;
	int			draw_mode;
	int			proj_mode;
	float		*zbuff;
	char		*data;
}				t_img;

typedef struct	s_ivtx
{
	long		x;
	long		y;
	float		z;
	float		elev;
	int			color;
}				t_ivtx;

typedef struct	s_ltracer
{
	int			p1[2];
	int			p2[2];
	int			d1;
	int			d2;
	int			xinc;
	int			yinc;
	int			cumul;
}				t_ltracer;

typedef struct	s_tracer
{
	t_ivtx		p1;
	t_ivtx		p2;
	int			flag;
	int			d1;
	int			d2;
	int			xinc;
	int			yinc;
	int			cumul;
}				t_tracer;

/*
** Vector initialization functions
*/

t_vec2			ft_init_vec2(float x, float y);
t_vec3			ft_init_vec3(float x, float y, float z);
t_vec4			ft_init_vec4(float x, float y, float z, float w);

/*
** Basic transformation matrices initialization functions
*/

t_mtx4			ft_translate(float t_x, float t_y, float t_z);
t_mtx4			ft_rotation(char axis, float pitch);
t_mtx4			ft_scale(float pitch_x, float pitch_y, float pitch_z);
t_mtx4			ft_identity(void);

/*
** Perspective matrices initialization functions
*/

t_mtx4			ft_orthographic(float top, float right, float near, float far);
t_mtx4			ft_perspective(float fovy, float aspect, float near, float far);

/*
** NDC and window coordinates conversion
*/

t_vec4			ft_ndc_conv(t_vec4 v);
void			ft_arr_ndc_conv(t_vtx *v, size_t size);
t_mtx4			ft_ndc_to_win(float x, float y, float width, float height);

/*
** rasterization functions
*/

void			ft_tri_rasterize(t_img *img, t_poly_lst *plst, t_vbuffer *buff);
t_tracer		init_tracer(t_ivtx p1, t_ivtx p2, t_ivtx p3);
void			draw_line(t_img *img, t_ivtx p1, t_ivtx p2, int btm);
t_tracer		point_calc(t_tracer tracer);
t_tracer		vec_orientation(t_tracer tracer);
float			elev_interpolate(t_ivtx p1, t_ivtx p2);
void			put_pixel(t_img	*img, t_ivtx pix, int edge);

/*
** Matrices operations functions
*/

t_mtx4			ft_mtx_mult(t_mtx4 mtx1, t_mtx4 mtx2);

/*
** vector operations functions
*/

t_vec4			ft_normalize(t_vec4 v);
float			ft_vec_norm(t_vec4 v);
void			ft_sort_by_y(t_poly_lst *plst, t_vbuffer *buff);

#endif
