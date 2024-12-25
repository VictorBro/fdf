/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_animation_update.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 20:23:51 by vbronov           #+#    #+#             */
/*   Updated: 2024/12/25 17:52:14 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	isometric_projection(t_vars *vars, t_coord a, t_coord *iso_a)
{
	int	zoom = 30;
	int offset_x = (vars->screen_width - vars->map_width * zoom) / 2;
	int offset_y = (vars->screen_height - vars->map_height * zoom) / 2; 

	iso_a->x = round((a.x - a.y) * cos(0.523599) * zoom + offset_x);
	iso_a->y = round(((a.x + a.y) * sin(0.523599) - a.z) * zoom + offset_y);
}

void	draw_map(t_vars *vars, t_img *frame)
{
	t_coord	iso_a;
	t_coord	iso_b;
	int y;
	int x;
	int	height_scale = 1;

	y = 0;
	while (y < vars->map_height)
	{
		x = 0;
		while (x < vars->map_width)
		{
			if (x + 1 < vars->map_width)
			{
				isometric_projection(vars, (t_coord){x, y, vars->map[y][x] * height_scale}, &iso_a);
				isometric_projection(vars, (t_coord){x + 1, y, vars->map[y][x + 1] * height_scale}, &iso_b);
				draw_line(frame, iso_a, iso_b, vars);
			}
			if (y + 1 < vars->map_height)
			{
				isometric_projection(vars, (t_coord){x, y, vars->map[y][x] * height_scale}, &iso_a);
				isometric_projection(vars, (t_coord){x, y + 1, vars->map[y + 1][x] * height_scale}, &iso_b);
				draw_line(frame, iso_a, iso_b, vars);
			}
			x++;
		}
		y++;
	}
}

int	update_frame(t_vars *vars)
{
	t_img	frame;

	if (vars->map == NULL)
		return (OK);
	frame.img = mlx_new_image(vars->mlx,
			vars->screen_width, vars->screen_height);
	if (frame.img == NULL)
		return (OK);
	frame.addr = mlx_get_data_addr(frame.img, &frame.bits_per_pixel,
			&frame.line_length, &frame.endian);
	if (frame.addr == NULL)
	{
		mlx_destroy_image(vars->mlx, frame.img);
		return (OK);
	}
	draw_map(vars, &frame);
	mlx_put_image_to_window(vars->mlx, vars->win, frame.img, 0, 0);
	mlx_destroy_image(vars->mlx, frame.img);

	//TODO: handle this case
	if (current_time_ms() - vars->last_measured_ms < FRAME_RATE_MS)
		return (OK);
	vars->last_measured_ms = current_time_ms();
	vars->frame_count = (vars->frame_count + 1) % 180;
	return (OK);
}
