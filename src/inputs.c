/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 12:07:04 by gmichaud          #+#    #+#             */
/*   Updated: 2017/09/29 18:44:24 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "inputs_osx.h"

static int		zoom_keys(int keycode, t_args *args)
{
	int		zoom;

	zoom = args->env->z_pitch;
	if (keycode == KEY_F)
	{
		args->env->proj_scale += zoom;
		args->map->view = ft_mtx_mult(ft_translate(0, 0, -zoom),
			args->map->view);
		if (!(update_img(args)))
			return (0);
	}
	if (keycode == KEY_R)
	{
		args->env->proj_scale -= zoom;
		args->map->view = ft_mtx_mult(ft_translate(0, 0, zoom),
			args->map->view);
		if (!(update_img(args)))
			return (0);
	}
	return (1);
}

static int		elev(int keycode, t_args *args)
{
	if (keycode == KEY_PAD_9 && args->env->z_scale < 20)
	{
		args->map->model = ft_mtx_mult(ft_scale(1, 1, 1.25), args->map->model);
		args->env->z_scale += 1;
		if (!(update_img(args)))
			return (0);
	}
	if (keycode == KEY_PAD_3 && args->env->z_scale > 0)
	{
		args->map->model = ft_mtx_mult(ft_scale(1, 1, 0.8), args->map->model);
		args->env->z_scale -= 1;
		if (!(update_img(args)))
			return (0);
	}
	return (1);
}

static int		modes(int keycode, t_args *args)
{
	if (keycode == KEY_M)
	{
		args->env->draw_mode = args->env->draw_mode ? 0 : 1;
		if (!(update_img(args)))
			return (0);
		put_params(args->env);
	}
	if (keycode == KEY_P)
	{
		args->env->proj_mode = args->env->proj_mode ? 0 : 1;
		if (!(update_img(args)))
			return (0);
		put_params(args->env);
	}
	return (1);
}

static int		options(int keycode, t_args *args)
{
	if (keycode == KEY_PAD_ADD && args->env->z_pitch < 2000)
	{
		args->env->z_pitch += 10;
		put_params(args->env);
	}
	if (keycode == KEY_PAD_SUB && args->env->z_pitch > 10)
	{
		args->env->z_pitch -= 10;
		put_params(args->env);
	}
	if (keycode == KEY_PAD_MULT && args->env->r_pitch < 180)
	{
		args->env->r_pitch += 1;
		put_params(args->env);
	}
	if (keycode == KEY_PAD_DIV && args->env->r_pitch > 1)
	{
		args->env->r_pitch -= 1;
		put_params(args->env);
	}
	return (1);
}

int				keypress(int keycode, void *args)
{
	t_env	*env;

	env = ((t_args*)args)->env;
	if (keycode == KEY_ESC)
		quit((t_args*)args);
	if (!rot_keys(keycode, (t_args*)args))
		error_display((t_args*)args);
	if (!zoom_keys(keycode, (t_args*)args))
		error_display((t_args*)args);
	if (!elev(keycode, (t_args*)args))
		error_display((t_args*)args);
	if (!modes(keycode, (t_args*)args))
		error_display((t_args*)args);
	options(keycode, (t_args*)args);
	return (1);
}
