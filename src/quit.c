/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 12:25:25 by gmichaud          #+#    #+#             */
/*   Updated: 2017/09/29 17:57:37 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		quit(t_args *args)
{
	if (args->map)
	{
		if (args->map->vlst)
		{
			if (args->map->vlst->cache)
				free(args->map->vlst->cache);
			if (args->map->vlst->data)
				free(args->map->vlst->data);
			free(args->map->vlst);
		}
		if (args->map->tiles)
		{
			if (args->map->tiles->data)
				free(args->map->tiles->data);
			free(args->map->tiles);
		}
		free(args->map);
	}
	mlx_destroy_window((void*)args->env->init, (void*)args->env->win);
	free(args->env->init);
	exit(0);
}
