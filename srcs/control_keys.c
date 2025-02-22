/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_keys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 21:47:27 by vbronov           #+#    #+#             */
/*   Updated: 2024/12/27 03:23:56 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_release(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
		ft_close(vars);
	return (OK);
}
