/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_keys_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 21:47:27 by vbronov           #+#    #+#             */
/*   Updated: 2024/12/29 17:09:18 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	key_press(int keycode, t_vars *vars)
{
	if (keycode == KEY_SHIFT_LEFT || keycode == KEY_SHIFT_RIGHT)
		vars->shift_pressed = TRUE;
	else if (keycode == KEY_UP)
	{
		vars->scale_altitude += ALTITUDE_FACTOR;
		vars->need_update = TRUE;
	}
	else if (keycode == KEY_DOWN)
	{
		vars->scale_altitude -= ALTITUDE_FACTOR;
		vars->need_update = TRUE;
	}
	else if (keycode == KEY_P)
	{
		vars->projection = (vars->projection + 1) % PROJECTIONS;
		vars->need_update = TRUE;
	}
	return (OK);
}

int	key_release(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
		ft_close(vars);
	else if (keycode == KEY_SHIFT_LEFT || keycode == KEY_SHIFT_RIGHT)
		vars->shift_pressed = FALSE;
	return (OK);
}

int	mouse_press(int button, int x, int y, t_vars *vars)
{
	double	new_zoom;
	double	mouse_wx;
	double	mouse_wy;

	if (button == 1)
	{
		vars->mouse_pressed = TRUE;
		vars->mouse_x = x;
		vars->mouse_y = y;
	}
	else if (button == 4 || button == 5)
	{
		new_zoom = vars->zoom;
		if (button == 4 && new_zoom < vars->zoom_max)
			new_zoom *= ZOOM_FACTOR;
		else if (button == 5 && new_zoom > vars->zoom_min)
			new_zoom /= ZOOM_FACTOR;
		mouse_wx = (x - vars->offset_x) / vars->zoom;
		mouse_wy = (y - vars->offset_y) / vars->zoom;
		vars->zoom = new_zoom;
		vars->offset_x = x - mouse_wx * new_zoom;
		vars->offset_y = y - mouse_wy * new_zoom;
		vars->need_update = TRUE;
	}
	return (OK);
}

int	mouse_release(int button, int x, int y, t_vars *vars)
{
	(void)x;
	(void)y;
	if (button == 1)
		vars->mouse_pressed = FALSE;
	return (OK);
}

int	mouse_move(int x, int y, t_vars *vars)
{
	int	dx;
	int	dy;

	if (vars->mouse_pressed)
	{
		dx = x - vars->mouse_x;
		dy = y - vars->mouse_y;
		if (vars->shift_pressed && vars->projection == ISOMETRIC)
		{
			vars->rot_z += dx * ROT_SPEED;
			if (vars->rot_z > 2 * M_PI)
				vars->rot_z -= 2 * M_PI;
			else if (vars->rot_z < -2 * M_PI)
				vars->rot_z += 2 * M_PI;
		}
		else
		{
			vars->offset_x += dx;
			vars->offset_y += dy;
		}
		vars->mouse_x = x;
		vars->mouse_y = y;
		vars->need_update = TRUE;
	}
	return (OK);
}
