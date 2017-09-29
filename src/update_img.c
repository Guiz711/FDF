/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 11:24:22 by gmichaud          #+#    #+#             */
/*   Updated: 2017/09/29 17:07:23 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		init_img(t_img *img, t_env *env)
{
	int i;

	img->draw_mode = env->draw_mode;
	img->proj_mode = env->proj_mode;
	img->color_depth = COLOR_DEPTH;
	img->width = REND_WIDTH * (COLOR_DEPTH / 8);
	img->height = WIN_HEIGHT;
	img->endian = ENDIAN;
	if (!(img->ptr = mlx_new_image(env->init, REND_WIDTH, img->height)))
		return (0);
	img->data = mlx_get_data_addr(img->ptr, &img->color_depth, &img->width,
		&img->endian);
	if (!(img->zbuff = (float*)malloc(sizeof(float) * REND_WIDTH * WIN_HEIGHT)))
		return (0);
	i = 0;
	while (i < REND_WIDTH * WIN_HEIGHT)
		img->zbuff[i++] = 2;
	return (1);
}

static int		create_cache(t_vbuffer *vlst)
{
	int i;

	if (!(vlst->cache))
		if (!(vlst->cache = (t_vtx*)malloc(sizeof(t_vtx) * vlst->size)))
			return (0);
	i = 0;
	while (i < vlst->size)
	{
		vlst->cache[i].pos = ft_init_vec4(vlst->data[i].pos.x,
			vlst->data[i].pos.y, vlst->data[i].pos.z, 1);
		vlst->cache[i].elev = vlst->data[i].elev;
		i++;
	}
	return (1);
}

static int		draw_map(t_img *img, t_env *env, t_map *map)
{
	t_mtx4	mv_mtx;
	t_mtx4	p_mtx;
	t_mtx4	mvp_mtx;

	if (!create_cache(map->vlst))
		return (0);
	mv_mtx = ft_mtx_mult(map->view, ft_mtx_mult(map->world, map->model));
	if (!img->proj_mode)
		p_mtx = ft_orthographic(env->proj_scale < 0 ? 0 : env->proj_scale,
			env->proj_scale < 0 ? 0 : env->proj_scale, -100, 5000);
	else
		p_mtx = ft_perspective(90, REND_WIDTH / WIN_HEIGHT, 1, 5000);
	mvp_mtx = ft_mtx_mult(p_mtx, mv_mtx);
	update_map(map, mvp_mtx);
	if (img->proj_mode)
		ft_arr_ndc_conv(map->vlst->cache, map->vlst->size);
	mvp_mtx = ft_ndc_to_win(REND_WIDTH * 0.5, WIN_HEIGHT * 0.5, REND_WIDTH,
		WIN_HEIGHT);
	update_map(map, mvp_mtx);
	ft_sort_by_y(map->tiles, map->vlst);
	ft_tri_rasterize(img, map->tiles, map->vlst);
	return (1);
}

int				update_img(t_args *args)
{
	t_env	*env;
	t_map	*map;
	t_img	img;

	env = args->env;
	map = args->map;
	if (!init_img(&img, env))
		return (0);
	if (!draw_map(&img, env, map))
		return (0);
	mlx_put_image_to_window(env->init, env->win, img.ptr, MENU_WIDTH, 0);
	mlx_destroy_image(env->init, img.ptr);
	free(img.zbuff);
	return (1);
}
