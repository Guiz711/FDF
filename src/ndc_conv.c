/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ndc_conv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 10:38:32 by gmichaud          #+#    #+#             */
/*   Updated: 2017/09/29 18:06:58 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmlxext.h"

/*
** ft_ndc_conv(t_vec4 v): normalizes a vector for Normalized Device Coordinates.
** returns a normalized vector.
**
** ft_arr_ndc_conv(t_vtx *v_arr, size_t size): normalizes an array of vertices
** into Normalized Device Coordinates.
** v_arr is a vertices array and size is the length of the array.
*/

t_vec4	ft_ndc_conv(t_vec4 v)
{
	t_vec4 v1;

	v1.x = v.x / v.w;
	v1.y = v.y / v.w;
	v1.z = v.z / v.w;
	v1.w = 1;
	return (v1);
}

void	ft_arr_ndc_conv(t_vtx *v_arr, size_t size)
{
	size_t i;

	i = 0;
	while (i < size)
	{
		v_arr[i].pos = ft_ndc_conv(v_arr[i].pos);
		i++;
	}
}
