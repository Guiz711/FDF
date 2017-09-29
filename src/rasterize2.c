/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 12:52:43 by gmichaud          #+#    #+#             */
/*   Updated: 2017/09/29 17:57:52 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmlxext.h"

float		elev_interpolate(t_ivtx p1, t_ivtx p2)
{
	float	delev;
	t_ivtx	vec;
	float	vlen;
	float	inc;

	vec.x = p2.x - p1.x;
	vec.y = p2.y - p1.y;
	vec.z = p2.z - p1.z;
	vlen = sqrt((float)(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
	delev = p2.elev - p1.elev;
	inc = delev / vlen;
	return (inc);
}

void		draw_line(t_img *img, t_ivtx p1, t_ivtx p2, int btm)
{
	t_ivtx	pix1;
	t_ivtx	pix2;
	float	inc;

	pix1 = p1.x < p2.x ? p1 : p2;
	pix2 = p1.x < p2.x ? p2 : p1;
	if (pix2.z >= pix1.z)
		pix1.z = pix2.z;
	inc = elev_interpolate(pix1, pix2);
	while (pix1.x <= pix2.x)
	{
		if (pix1.x == p1.x || pix1.x == p2.x || btm == 1)
			put_pixel(img, pix1, 1);
		else
			put_pixel(img, pix1, 0);
		pix1.elev += inc;
		pix1.x++;
	}
}

t_tracer	point_calc(t_tracer tracer)
{
	if (tracer.flag)
		tracer.p1.x += tracer.xinc;
	else
		tracer.p1.y += tracer.yinc;
	tracer.cumul += tracer.d2;
	if (tracer.cumul >= tracer.d1)
	{
		tracer.cumul -= tracer.d1;
		if (tracer.flag)
			tracer.p1.y += tracer.yinc;
		else
			tracer.p1.x += tracer.xinc;
	}
	return (tracer);
}

t_tracer	vec_orientation(t_tracer tracer)
{
	int	tmp;

	tmp = 0;
	tracer.xinc = tracer.d1 > 0 ? 1 : -1;
	tracer.yinc = tracer.d2 > 0 ? 1 : -1;
	tracer.d1 = abs(tracer.d1);
	tracer.d2 = abs(tracer.d2);
	if (tracer.d1 > tracer.d2)
	{
		tracer.flag = 1;
	}
	else
	{
		tracer.flag = 0;
		tmp = tracer.d1;
		tracer.d1 = tracer.d2;
		tracer.d2 = tmp;
	}
	tracer.cumul = tracer.d1 / 2;
	return (tracer);
}

t_tracer	init_tracer(t_ivtx p1, t_ivtx p2, t_ivtx p3)
{
	t_tracer	trac;

	trac.p1 = p1;
	trac.p2 = p2;
	if (p1.z >= p2.z && p1.z >= p3.z)
		trac.p1.z = p1.z;
	else if (p2.z >= p1.z && p2.z >= p3.z)
		trac.p1.z = p2.z;
	else
		trac.p1.z = p3.z;
	trac.d1 = trac.p2.x - trac.p1.x;
	trac.d2 = trac.p2.y - trac.p1.y;
	trac = vec_orientation(trac);
	return (trac);
}
