/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 20:23:51 by vbronov           #+#    #+#             */
/*   Updated: 2024/12/28 19:10:07 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include <stdio.h>

// static void rotate_x(double *y, double *z, double angle)
// {
// 	double old_y = *y;
// 	double old_z = *z;
	
// 	*y = old_y * cos(angle) - old_z * sin(angle);
// 	*z = old_y * sin(angle) + old_z * cos(angle);
// }

// static void rotate_y(double *x, double *z, double angle)
// {
// 	double old_x = *x;
// 	double old_z = *z;
	
// 	*x = old_x * cos(angle) + old_z * sin(angle);
// 	*z = -old_x * sin(angle) + old_z * cos(angle);
// }

static void rotate_z(double *x, double *y, double angle)
{
	double old_x = *x;
	double old_y = *y;
	
	*x = old_x * cos(angle) - old_y * sin(angle);
	*y = old_x * sin(angle) + old_y * cos(angle);
	// printf("angle: %f, sin: %f, cos: %f\n", angle * 180 / M_PI, sin(angle), cos(angle));
	// printf("old_x: %f, old_y: %f, x: %f, y: %f\n", old_x, old_y, *x, *y);
}

// Main rotation function with corrected order and normalized angles
static void rotate_point(double *x, double *y, double *z, t_vars *vars)
{
	// Normalize coordinates to origin before rotation
	double cx = *x - (vars->map_width-1) / 2.0;
	double cy = *y - (vars->map_height-1) / 2.0;
	double cz = *z;

	// Apply rotations in Z-Y-X order (this order typically feels more natural)
	rotate_z(&cx, &cy, vars->rot_z);
	// rotate_y(&cx, &cz, vars->rot_y);
	// rotate_x(&cy, &cz, vars->rot_x);

	// Return to world coordinates
	*x = cx + (vars->map_width-1) / 2.0;
	*y = cy + (vars->map_height-1) / 2.0;
	*z = cz;
}

static void isometric_projection(t_vars *vars, t_coord a, t_coord *iso_a)
{
	double	x;
	double	y;
	double	z;

	x = a.x;
	y = a.y;
	z = a.z;
	rotate_point(&x, &y, &z, vars);
	iso_a->x = round((x - y) * cos(0.523599) * vars->zoom + vars->offset_x);
	iso_a->y = round(((x + y) * sin(0.523599) - z) * vars->zoom + vars->offset_y);
}

static void	draw_horizontal_line(t_vars *vars, t_img *frame,
			t_coord iso_a, t_coord pos)
{
	t_coord	iso_b;

	isometric_projection(vars, (t_coord){pos.x + 1, pos.y,
		vars->map[pos.y][pos.x + 1] * vars->scale_altitude}, &iso_b);
	iso_b.z = vars->colors[pos.y][pos.x + 1];
	draw_line(frame, iso_a, iso_b, vars);
}

static void	draw_vertical_line(t_vars *vars, t_img *frame,
			t_coord iso_a, t_coord pos)
{
	t_coord	iso_b;

	isometric_projection(vars, (t_coord){pos.x, pos.y + 1,
		vars->map[pos.y + 1][pos.x] * vars->scale_altitude}, &iso_b);
	iso_b.z = vars->colors[pos.y + 1][pos.x];
	draw_line(frame, iso_a, iso_b, vars);
}

void	draw_map(t_vars *vars, t_img *frame)
{
	t_coord	iso_a;
	t_coord	pos;

	pos.y = 0;
	while (pos.y < vars->map_height)
	{
		pos.x = 0;
		while (pos.x < vars->map_width)
		{
			isometric_projection(vars, (t_coord){pos.x, pos.y,
				vars->map[pos.y][pos.x] * vars->scale_altitude}, &iso_a);
			iso_a.z = vars->colors[pos.y][pos.x];
			if (pos.x + 1 < vars->map_width)
				draw_horizontal_line(vars, frame, iso_a, pos);
			if (pos.y + 1 < vars->map_height)
				draw_vertical_line(vars, frame, iso_a, pos);
			pos.x++;
		}
		pos.y++;
	}
}
