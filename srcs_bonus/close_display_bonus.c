/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_display_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 04:04:40 by vbronov           #+#    #+#             */
/*   Updated: 2024/12/27 04:12:31 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

// Singletone
int	ft_close(t_vars *vars)
{
	static int	closed;

	if (!closed)
	{
		closed++;
		free_map(vars);
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_loop_end(vars->mlx);
	}
	ft_printf("Exited\n");
	if (OS_LINUX == FALSE)
		exit (0);
	return (OK);
}
