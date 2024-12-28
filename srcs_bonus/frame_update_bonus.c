/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_update_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 20:23:51 by vbronov           #+#    #+#             */
/*   Updated: 2024/12/27 04:12:47 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static long long	current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL));
}

int	update_frame(t_vars *vars)
{
	t_img	frame;

	if (vars->need_update == FALSE)
		return (OK);
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
	vars->need_update = FALSE;

	//TODO: handle this case
	if (current_time_ms() - vars->last_measured_ms < FRAME_RATE_MS)
		return (OK);
	vars->last_measured_ms = current_time_ms();
	vars->frame_count = (vars->frame_count + 1) % 180;
	return (OK);
}
