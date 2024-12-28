/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 23:11:50 by vbronov           #+#    #+#             */
/*   Updated: 2024/12/27 02:12:52 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "fdf.h"

void	get_isometric_bounds(t_vars *vars, t_coord *xy_min, t_coord *xy_max)
{
	int		x;
	int		y;
	double	iso_x;
	double	iso_y;
	int		z;

	*xy_min = (t_coord){INT_MAX, INT_MAX, 0};
	*xy_max = (t_coord){INT_MIN, INT_MIN, 0};
	y = 0;
	while (y < vars->map_height)
	{
		x = 0;
		while (x < vars->map_width)
		{
			z = vars->map[y][x] * vars->scale_altitude;
			iso_x = round((x - y) * cos(0.523599));
			iso_y = round((x + y) * sin(0.523599) - z);
			xy_min->x = fmin(xy_min->x, iso_x);
			xy_min->y = fmin(xy_min->y, iso_y);
			xy_max->x = fmax(xy_max->x, iso_x);
			xy_max->y = fmax(xy_max->y, iso_y);
			x++;
		}
		y++;
	}
}

void	init_transform(t_vars *vars)
{
	t_coord	xy_min;
	t_coord	xy_max;
	int		projected_width;
	int		projected_height;
	t_coord	xy_zoom;

	get_isometric_bounds(vars, &xy_min, &xy_max);
	projected_width = xy_max.x - xy_min.x;
	projected_height = xy_max.y - xy_min.y;
	if (projected_width > 0 && projected_height > 0)
	{
		xy_zoom.x = (vars->screen_width - PADDING * 2) / projected_width;
		xy_zoom.y = (vars->screen_height - PADDING * 2) / projected_height;
		vars->zoom = fmin(xy_zoom.x, xy_zoom.y);
		if (vars->zoom < 1)
			vars->zoom = 1;
	}
	projected_width *= vars->zoom;
	projected_height *= vars->zoom;
	vars->offset_x = (vars->screen_width - projected_width) / 2
		- xy_min.x * vars->zoom;
	vars->offset_y = (vars->screen_height - projected_height) / 2
		- xy_min.y * vars->zoom;
}
