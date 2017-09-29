/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 15:55:18 by gmichaud          #+#    #+#             */
/*   Updated: 2017/09/29 17:01:39 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmlxext.h"

/*
** ft_frustrum_mtx(float top, float rigth, float near, float far) :
** Creates a perspective projection matrix.
** The parameters are the top, right, near and far clipping planes.
** returns a t_mtx4 matrix representing the transformation.
**
** ft_perspective(float fovy, float aspect, float near, float far) :
** Creates a perspective projection matrix.
** fovy: the Y axis field of view.
** aspect: the aspect ratio of the window.
** near: near clipping plane.
** far: far clipping plane.
** returns a t_mtx4 matrix representing the tranformation.
**
** ft_orthographic(float top, float  right, float near, float far) :
** Creates an orthogonal projection matrice.
** The parameters are the top, right, near and far clipping planes.
** returns a t_mtx4 matrix representing the transformation.
*/

static t_mtx4	ft_frustum_mtx(float top, float right, float near, float far)
{
	t_mtx4	m;

	m.a[0] = 2 * near / (2 * right);
	m.a[1] = 0;
	m.a[2] = 0;
	m.a[3] = 0;
	m.b[0] = 0;
	m.b[1] = 2 * near / (2 * top);
	m.b[2] = 0;
	m.b[3] = 0;
	m.c[0] = 0;
	m.c[1] = 0;
	m.c[2] = -(far + near) / (far - near);
	m.c[3] = -(2 * far * near) / (far - near);
	m.d[0] = 0;
	m.d[1] = 0;
	m.d[2] = -1;
	m.d[3] = 0;
	return (m);
}

t_mtx4			ft_perspective(float fovy, float aspect, float near, float far)
{
	t_mtx4	m;
	float	top;
	float	right;

	top = near * tanf(fovy * (M_PI / 360));
	right = top * aspect;
	m = ft_frustum_mtx(top, right, near, far);
	return (m);
}

t_mtx4			ft_orthographic(float top, float right, float near, float far)
{
	t_mtx4	m;

	m.a[0] = 1 / right;
	m.a[1] = 0;
	m.a[2] = 0;
	m.a[3] = 0;
	m.b[0] = 0;
	m.b[1] = 1 / top;
	m.b[2] = 0;
	m.b[3] = 0;
	m.c[0] = 0;
	m.c[1] = 0;
	m.c[2] = -2 / (far - near);
	m.c[3] = -((far + near) / (far - near));
	m.d[0] = 0;
	m.d[1] = 0;
	m.d[2] = 0;
	m.d[3] = 1;
	return (m);
}
