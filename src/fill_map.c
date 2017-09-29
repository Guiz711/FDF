/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 11:53:37 by guizmo            #+#    #+#             */
/*   Updated: 2017/09/29 16:59:55 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_poly_lst	*init_plst(int w, int h)
{
	t_poly_lst	*plst;

	if (!(plst = (t_poly_lst*)malloc(sizeof(t_poly_lst))))
		return (NULL);
	plst->p_size = 3;
	plst->p_cnt = (w - 1) * (h - 1) * 2;
	if (!(plst->data = (int*)malloc(sizeof(int) * plst->p_size * plst->p_cnt)))
		return (NULL);
	return (plst);
}

t_poly_lst			*create_polys(int w, int h)
{
	t_poly_lst	*plst;
	int			i;
	int			j;

	if (!(plst = init_plst(w, h)))
		return (NULL);
	i = 0;
	j = 0;
	while (i < w * h)
	{
		if (i % w != (w - 1) && i / w != h - 1)
		{
			plst->data[j++] = i;
			plst->data[j++] = i + 1;
			plst->data[j++] = i + w;
		}
		if (i / w != 0 && i % w != 0)
		{
			plst->data[j++] = i;
			plst->data[j++] = i - 1;
			plst->data[j++] = i - w;
		}
		i++;
	}
	return (plst);
}

static int			init_vlst(t_map *map, int len)
{
	if (!(map->vlst->data =
		(t_vtx*)malloc(sizeof(t_vtx) * map->height * len)))
		return (0);
	map->vlst->size = map->height * len;
	map->width = len;
	return (1);
}

int					fill_map(t_map *map, char **point_list)
{
	int			len;
	int			j;
	static int	i = 0;

	len = 0;
	while (point_list[len])
		len++;
	if (!i)
	{
		if (!init_vlst(map, len))
			return (0);
	}
	if (len != map->width)
		return (0);
	j = 0;
	while (j < len)
	{
		map->vlst->data[i].pos = ft_init_vec4(j, i / map->width,
			ft_atoi(point_list[j]), 1);
		map->vlst->data[i].elev = map->vlst->data[i].pos.z;
		i++;
		j++;
	}
	return (1);
}
