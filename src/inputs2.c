/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 11:57:33 by gmichaud          #+#    #+#             */
/*   Updated: 2017/09/29 17:56:25 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "inputs_osx.h"

static int		rotation(char axis, int sign, t_args *args)
{
	int	rot;

	rot = args->env->r_pitch;
	args->map->world = ft_mtx_mult(ft_rotation(axis, sign * rot * (M_PI / 180)),
		args->map->world);
	if (!(update_img(args)))
		return (0);
	return (1);
}

int				rot_keys(int keycode, t_args *args)
{
	if (keycode == KEY_S)
		if (!rotation('x', -1, args))
			return (0);
	if (keycode == KEY_W)
		if (!rotation('x', 1, args))
			return (0);
	if (keycode == KEY_A)
		if (!rotation('y', -1, args))
			return (0);
	if (keycode == KEY_D)
		if (!rotation('y', 1, args))
			return (0);
	if (keycode == KEY_Q)
		if (!rotation('z', -1, args))
			return (0);
	if (keycode == KEY_E)
		if (!rotation('z', 1, args))
			return (0);
	return (1);
}
