/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 20:23:51 by vbronov           #+#    #+#             */
/*   Updated: 2024/12/29 17:10:07 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	isometric_projection(t_vars *vars, t_coord a, t_coord *iso_a)
{
	double	x;
	double	y;
	double	z;

	x = a.x;
	y = a.y;
	z = a.z;
	rotate_point(&x, &y, &z, vars);
	iso_a->x = round((x - y) * cos(0.523599) * vars->zoom + vars->offset_x);
	iso_a->y = round(((x + y) * sin(0.523599) - z) * vars->zoom
			+ vars->offset_y);
}

static void	orthographic_top(t_vars *vars, t_coord a, t_coord *ortho_a)
{
	double	x;
	double	y;
	double	z;

	x = a.x - (vars->map_width - 1) / 2.0;
	y = a.y - (vars->map_height - 1) / 2.0;
	z = a.z;
	ortho_a->x = round(x * vars->zoom + vars->offset_x);
	ortho_a->y = round(y * vars->zoom + vars->offset_y);
	ortho_a->z = z;
}

static void	orthographic_front(t_vars *vars, t_coord a, t_coord *ortho_a)
{
	double	x;
	double	z;

	x = a.x - (vars->map_width - 1) / 2.0;
	z = a.z;
	ortho_a->x = round(x * vars->zoom + vars->offset_x);
	ortho_a->y = round(-z * vars->zoom + vars->offset_y);
	ortho_a->z = z;
}

static void	orthographic_side(t_vars *vars, t_coord a, t_coord *ortho_a)
{
	double	y;
	double	z;

	y = a.y - (vars->map_height - 1) / 2.0;
	z = a.z;
	ortho_a->x = round(y * vars->zoom + vars->offset_x);
	ortho_a->y = round(-z * vars->zoom + vars->offset_y);
	ortho_a->z = z;
}

void	project_point(t_vars *vars, t_coord a, t_coord *proj_a)
{
	if (vars->projection == ISOMETRIC)
		isometric_projection(vars, a, proj_a);
	else if (vars->projection == ORTHOGRAPHIC_FRONT)
		orthographic_front(vars, a, proj_a);
	else if (vars->projection == ORTHOGRAPHIC_SIDE)
		orthographic_side(vars, a, proj_a);
	else
		orthographic_top(vars, a, proj_a);
}
