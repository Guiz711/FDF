/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 16:29:15 by gmichaud          #+#    #+#             */
/*   Updated: 2017/09/29 18:42:52 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmlxext.h"

static void		fill_triangle(t_img *img, t_ivtx p1, t_ivtx p2, t_ivtx p3)
{
	t_tracer	trac[2];
	int			i[2];
	float		inc[2];

	trac[0] = init_tracer(p1, p2, p3);
	trac[1] = init_tracer(p1, p3, p2);
	inc[0] = elev_interpolate(trac[0].p1, trac[0].p2);
	inc[1] = elev_interpolate(trac[1].p1, trac[1].p2);
	i[0] = 0;
	i[1] = 0;
	while (i[0]++ <= trac[0].d1)
	{
		if (img->draw_mode)
			draw_line(img, trac[0].p1, trac[1].p1, 0);
		put_pixel(img, trac[0].p1, 1);
		trac[0] = point_calc(trac[0]);
		trac[0].p1.elev += inc[0];
		while (trac[0].p1.y != trac[1].p1.y && i[1]++ <= trac[1].d1)
		{
			put_pixel(img, trac[1].p1, 1);
			trac[1] = point_calc(trac[1]);
			trac[1].p1.elev += inc[1];
		}
	}
}

static t_ivtx	init_img_vtx(t_vtx p)
{
	t_ivtx	i_p;

	i_p.x = p.pos.x >= 0 ? (long)(p.pos.x + 0.5) : (long)(p.pos.x - 0.5);
	i_p.y = p.pos.y >= 0 ? (long)(p.pos.y + 0.5) : (long)(p.pos.y - 0.5);
	i_p.z = p.pos.z;
	i_p.elev = p.elev;
	return (i_p);
}

static void		triangle_type(t_img *img, t_vtx p1, t_vtx p2, t_vtx p3)
{
	t_ivtx	i_p1;
	t_ivtx	i_p2;
	t_ivtx	i_p3;

	i_p1 = init_img_vtx(p1);
	i_p2 = init_img_vtx(p2);
	i_p3 = init_img_vtx(p3);
	if (i_p1.y == i_p2.y)
	{
		draw_line(img, i_p1, i_p2, 1);
		fill_triangle(img, i_p3, i_p1, i_p2);
	}
	else if (i_p2.y == i_p3.y)
	{
		draw_line(img, i_p2, i_p3, 1);
		fill_triangle(img, i_p1, i_p2, i_p3);
	}
	else
	{
		fill_triangle(img, i_p1, i_p2, i_p3);
		fill_triangle(img, i_p3, i_p2, i_p1);
	}
}

void			ft_tri_rasterize(t_img *img, t_poly_lst *plst, t_vbuffer *buff)
{
	int		i;
	t_vtx	p1;
	t_vtx	p2;
	t_vtx	p3;

	i = 0;
	while (i < plst->p_size * plst->p_cnt)
	{
		p1 = buff->cache[plst->data[i]];
		p2 = buff->cache[plst->data[i + 1]];
		p3 = buff->cache[plst->data[i + 2]];
		triangle_type(img, p1, p2, p3);
		i += 3;
	}
}
