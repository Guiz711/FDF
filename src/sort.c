/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 11:33:05 by gmichaud          #+#    #+#             */
/*   Updated: 2017/09/29 17:03:28 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmlxext.h"

static void		swap(int *a, int *b)
{
	int c;

	c = *a;
	*a = *b;
	*b = c;
}

void			ft_sort_by_y(t_poly_lst *plst, t_vbuffer *buff)
{
	int		i;
	t_vtx	*v;
	int		*p;

	i = 0;
	v = buff->cache;
	p = plst->data;
	while (i < plst->p_size * plst->p_cnt)
	{
		if (v[p[i]].pos.y > v[p[i + 1]].pos.y)
			swap(&p[i], &p[i + 1]);
		if (v[p[i]].pos.y > v[p[i + 2]].pos.y)
			swap(&p[i], &p[i + 2]);
		if (v[p[i + 1]].pos.y > v[p[i + 2]].pos.y)
			swap(&p[i + 1], &p[i + 2]);
		i += 3;
	}
}
