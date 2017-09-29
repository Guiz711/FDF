/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 10:59:08 by gmichau           #+#    #+#             */
/*   Updated: 2017/09/29 17:57:15 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		clear_params(t_env *env)
{
	void *img;

	if (!(img = mlx_new_image(env->init, MENU_WIDTH, 100)))
		return (0);
	mlx_put_image_to_window(env->init, env->win, img, 0, WIN_HEIGHT - 100);
	mlx_destroy_image((void*)env->init, (void*)img);
	return (1);
}

static void		put_mode(t_env *env)
{
	if (env->proj_mode)
		mlx_string_put(env->init, env->win, 20, WIN_HEIGHT - 80, 0xFFFFFF,
			"Projection mode   : Perspective");
	else
		mlx_string_put(env->init, env->win, 20, WIN_HEIGHT - 80, 0xFFFFFF,
			"Projection mode   : Orthographic");
	if (env->draw_mode)
		mlx_string_put(env->init, env->win, 20, WIN_HEIGHT - 60, 0xFFFFFF,
			"Drawing mode      : Filled polygons");
	else
		mlx_string_put(env->init, env->win, 20, WIN_HEIGHT - 60, 0xFFFFFF,
			"Drawing mode      : Wireframe");
}

int				put_params(t_env *env)
{
	char	*line;
	char	*param;

	clear_params(env);
	if (!(param = ft_itoa((int)env->r_pitch)))
		return (0);
	if (!(line = ft_strjoin("Rotation pitch    : ", param)))
		return (0);
	ft_strdel(&param);
	mlx_string_put(env->init, env->win, 20, WIN_HEIGHT - 40, 0xFFFFFF, line);
	ft_strdel(&line);
	if (!(param = ft_itoa((int)env->z_pitch)))
		return (0);
	if (!(line = ft_strjoin("Translation pitch : ", param)))
		return (0);
	ft_strdel(&param);
	mlx_string_put(env->init, env->win, 20, WIN_HEIGHT - 20, 0xFFFFFF, line);
	ft_strdel(&line);
	put_mode(env);
	return (1);
}
