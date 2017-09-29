/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 11:28:29 by gmichaud          #+#    #+#             */
/*   Updated: 2017/09/29 18:44:39 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		get_map_size(char *map_file)
{
	char	*map_line;
	int		ret;
	int		size;
	int		fd;

	map_line = NULL;
	size = 0;
	if ((fd = open(map_file, O_RDONLY)) == -1)
		return (0);
	while ((ret = get_next_line(fd, &map_line)) > 0)
	{
		free(map_line);
		size++;
	}
	close(fd);
	return (size);
}

static int		init_map(char *map_file, t_map *map)
{
	if (!(map->vlst = (t_vbuffer*)ft_memalloc(sizeof(t_vbuffer))))
		return (0);
	map->vlst->cache = NULL;
	map->vlst->data = NULL;
	map->tiles = NULL;
	map->vlst->size = 0;
	map->width = 0;
	if (!(map->height = get_map_size(map_file)))
		return (0);
	return (1);
}

static void		free_point_list(char ***point_list)
{
	char	**tmp;

	if (!point_list)
		return ;
	tmp = *point_list;
	if (tmp)
	{
		while (*tmp)
		{
			free(*tmp);
			tmp++;
		}
		free(*point_list);
	}
	*point_list = NULL;
}

static int		get_map(char *map_file, t_map *map)
{
	int		fd;
	int		ret;
	int		error;
	char	*map_line;
	char	**point_list;

	map_line = NULL;
	if (!init_map(map_file, map))
		return (0);
	if ((fd = open(map_file, O_RDONLY)) == -1)
		return (0);
	error = 1;
	while ((ret = get_next_line(fd, &map_line)) > 0 && error)
	{
		if (!(point_list = ft_strsplit(map_line, ' ')))
			error = 0;
		ft_memdel((void**)&map_line);
		if (!fill_map(map, point_list))
			error = 0;
		free_point_list(&point_list);
	}
	close(fd);
	if (ret == -1 || !(map->width) || !error)
		return (0);
	return (1);
}

int				init_params(t_args *args, char *map_file)
{
	t_map	*map;
	t_env	*env;
	t_mtx4	w;

	env = args->env;
	if (!(map = (t_map*)malloc(sizeof(t_map))))
		return (0);
	args->map = map;
	if (!get_map(map_file, map))
		return (0);
	if (!(map->tiles = create_polys(map->width, map->height)))
		return (0);
	args->env->z_pitch = 10;
	args->env->r_pitch = 10;
	args->env->draw_mode = 0;
	args->env->proj_mode = 0;
	args->env->proj_scale = map->width + map->height;
	args->env->z_scale = 8;
	w = ft_translate(-((float)map->width / 2), -((float)map->height / 2), 0);
	map->model = ft_mtx_mult(ft_scale(1, 1, 0.1), w);
	map->world = ft_mtx_mult(ft_rotation('x', 60 * (M_PI / 180)),
		ft_rotation('z', 45 * (M_PI / 180)));
	map->view = ft_translate(0, 0, -(map->width + map->height));
	return (1);
}
