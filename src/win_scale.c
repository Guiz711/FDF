/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_scale.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 10:28:02 by gmichaud          #+#    #+#             */
/*   Updated: 2017/09/29 17:58:04 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmlxext.h"

t_mtx4	ft_ndc_to_win(float x, float y, float width, float height)
{
	t_mtx4 m1;
	t_mtx4 m2;
	t_mtx4 final;

	m1 = ft_scale(width, height * (width / height), 1);
	m2 = ft_translate(x, y, 0);
	final = ft_mtx_mult(m2, m1);
	return (final);
}
