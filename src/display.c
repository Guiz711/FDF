/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 11:04:04 by gmichaud          #+#    #+#             */
/*   Updated: 2017/09/29 17:50:47 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		fill_menu(t_env *env)
{
	int		fd;
	int		ret;
	char	*line;
	int		pos[2];

	pos[0] = 20;
	pos[1] = 0;
	line = NULL;
	if ((fd = open("menu.cfg", O_RDONLY)) == -1)
		return (0);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		pos[1] += 20;
		if (pos[1] < WIN_HEIGHT)
			mlx_string_put(env->init, env->win, pos[0], pos[1], 0xFFFFFF, line);
		ft_memdel((void**)&line);
	}
	close(fd);
	if (ret == -1)
		return (0);
	return (1);
}

int		win_draw(void *args)
{
	t_env	*env;
	t_map	*map;

	env = ((t_args*)args)->env;
	map = ((t_args*)args)->map;
	if (!update_img((t_args*)args))
		error_display((t_args*)args);
	if (!fill_menu(env))
		error_display((t_args*)args);
	put_params(env);
	return (1);
}
