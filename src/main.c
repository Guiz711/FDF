/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 12:23:23 by gmichaud          #+#    #+#             */
/*   Updated: 2017/09/29 17:51:02 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "inputs_osx.h"

static void		init_args(t_env *env, t_args *args)
{
	env->init = NULL;
	env->win = NULL;
	env->z_pitch = 0;
	env->r_pitch = 0;
	env->draw_mode = 0;
	env->proj_mode = 0;
	env->proj_scale = 0;
	args->map = NULL;
}

int				main(int argc, char **argv)
{
	t_env	env;
	t_args	args;

	init_args(&env, &args);
	args.env = &env;
	if (argc != 2)
		return (0);
	if (!(env.init = mlx_init()))
		return (error_mlx());
	if (!(env.win = mlx_new_window(env.init, WIN_WIDTH, WIN_HEIGHT, "FDF")))
		return (error_win());
	if (!init_params(&args, argv[1]))
		error_map(&args);
	mlx_expose_hook(env.win, &win_draw, &args);
	mlx_hook(env.win, KEYPRESS, KEYPRESSMASK, &keypress, &args);
	mlx_loop(env.init);
	return (0);
}
