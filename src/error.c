/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 11:16:07 by gmichaud          #+#    #+#             */
/*   Updated: 2017/09/29 16:57:49 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		error_mlx(void)
{
	ft_putendl_fd("Error, mlx couldn't be initialised", 2);
	return (0);
}

int		error_win(void)
{
	ft_putendl_fd("Error, the window couldn't be initialised", 2);
	return (0);
}

void	error_map(t_args *args)
{
	ft_putendl_fd("Error, the map couldn't be read", 2);
	quit(args);
}

void	error_display(t_args *args)
{
	ft_putendl_fd("Display Error", 2);
	quit(args);
}
