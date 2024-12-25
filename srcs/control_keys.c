/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_keys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 21:47:27 by vbronov           #+#    #+#             */
/*   Updated: 2024/12/25 21:47:31 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_press(int keycode, t_vars *vars)
{
	if (keycode != KEY_UP && keycode != KEY_DOWN && keycode != KEY_RIGHT
		&& keycode != KEY_LEFT)
		return (OK);
	//TODO: handle this case
	(void)vars;
	return (OK);
}

int	key_release(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
		ft_close(vars);
	return (OK);
}

int	mouse_press(int button, int x, int y, t_vars *vars)
{
	if (button == 1)
	{
		if (x < 0 || x >= vars->screen_width
			|| y < 0 || y >= vars->screen_height)
			return (OK);
		vars->mousedown = 1;
		vars->mouse_x = x;
		vars->mouse_y = y;
	}
	//TODO add zoom in and zoom out
	return (OK);
}

int	mouse_release(int button, int x, int y, t_vars *vars)
{
	(void)x;
	(void)y;
	if (button == 1)
		vars->mousedown = 0;
	return (OK);
}

int	mouse_move(int x, int y, t_vars *vars)
{
	if (x < 0 || x >= vars->screen_width || y < 0 || y >= vars->screen_height)
		return (OK);
	if (vars->mousedown)
		ft_printf("Mouse move coordinates x = %d, y = %d\n", x, y);
	return (OK);
}
