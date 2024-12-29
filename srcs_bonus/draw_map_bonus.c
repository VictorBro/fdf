/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 20:23:51 by vbronov           #+#    #+#             */
/*   Updated: 2024/12/29 17:07:56 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	draw_horizontal_line(t_vars *vars, t_img *frame,
			t_coord iso_a, t_coord pos)
{
	t_coord	iso_b;

	project_point(vars, (t_coord){pos.x + 1, pos.y,
		vars->map[pos.y][pos.x + 1] * vars->scale_altitude}, &iso_b);
	iso_b.z = vars->colors[pos.y][pos.x + 1];
	draw_line(frame, iso_a, iso_b, vars);
}

static void	draw_vertical_line(t_vars *vars, t_img *frame,
			t_coord iso_a, t_coord pos)
{
	t_coord	iso_b;

	project_point(vars, (t_coord){pos.x, pos.y + 1,
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
			project_point(vars, (t_coord){pos.x, pos.y,
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
