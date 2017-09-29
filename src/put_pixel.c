/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 12:48:16 by gmichaud          #+#    #+#             */
/*   Updated: 2017/09/29 17:57:25 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmlxext.h"

/*
** put_pixel(t_img *img, t_ivtx pix, int edge) :
** colorizes a pixel in the img buffer by using the pix vertex coordinates.
** The color is chosen in function of the elevation and the position
** of the pixel (is it belonging to the edge or the inside of a polygon?).
*/

static int		color_choose(float elev)
{
	if (elev <= 0)
		return (0x00000099);
	else if (elev < 100)
		return (0x00669900);
	else if (elev < 180)
		return (0x00666600);
	else
		return (0x00CCCCCC);
}

static void		edge_color(int *color)
{
	unsigned char	*rgb;
	int				i;

	rgb = (unsigned char*)color;
	i = 0;
	while (i < 4)
	{
		if (rgb[i])
			rgb[i] -= 0x22;
		i++;
	}
}

void			put_pixel(t_img *img, t_ivtx pix, int edge)
{
	char	*data;
	int		width;
	int		inc;
	int		col;

	data = img->data;
	inc = img->color_depth / 8;
	width = img->width;
	if (pix.x < (img->width / inc) && pix.y < img->height && pix.x >= 0
		&& pix.y >= 0 && pix.z >= -1 && pix.z <= 1)
	{
		if (img->zbuff[pix.y * (width / inc) + pix.x] > pix.z
			|| (img->zbuff[pix.y * (width / inc) + pix.x] >= pix.z && edge))
		{
			img->zbuff[pix.y * (width / inc) + pix.x] = pix.z;
			col = color_choose(pix.elev);
			if (edge)
				edge_color(&col);
			ft_memcpy(&data[(pix.y * width) + (pix.x * inc)], &col,
				sizeof(col));
		}
	}
}
