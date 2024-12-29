/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 20:23:51 by vbronov           #+#    #+#             */
/*   Updated: 2024/12/29 17:09:29 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	rotate_z(double *x, double *y, double angle)
{
	double	old_x;
	double	old_y;

	old_x = *x;
	old_y = *y;
	*x = old_x * cos(angle) - old_y * sin(angle);
	*y = old_x * sin(angle) + old_y * cos(angle);
}

void	rotate_point(double *x, double *y, double *z, t_vars *vars)
{
	double	cx;
	double	cy;
	double	cz;

	cx = *x - (vars->map_width - 1) / 2.0;
	cy = *y - (vars->map_height - 1) / 2.0;
	cz = *z;
	rotate_z(&cx, &cy, vars->rot_z);
	*x = cx + (vars->map_width - 1) / 2.0;
	*y = cy + (vars->map_height - 1) / 2.0;
	*z = cz;
}
