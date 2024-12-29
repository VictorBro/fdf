/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fdf_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 13:03:53 by vbronov           #+#    #+#             */
/*   Updated: 2024/12/29 16:40:56 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	init_vars(t_vars *vars)
{
	vars->mlx = NULL;
	vars->win = NULL;
	vars->map = NULL;
	vars->colors = NULL;
	vars->map_height = -1;
	vars->map_width = -1;
	vars->screen_width = DEFAULT_SCREEN_WIDTH;
	vars->screen_height = DEFAULT_SCREEN_HEIGHT;
	vars->mouse_pressed = FALSE;
	vars->mouse_x = 0;
	vars->mouse_y = 0;
	vars->need_update = TRUE;
	vars->zoom = DEFAULT_ZOOM;
	vars->zoom_min = DEFAULT_ZOOM * MIN_ZOOM_FACTOR;
	vars->zoom_max = DEFAULT_ZOOM * MAX_ZOOM_FACTOR;
	vars->scale_altitude = 1.0;
	vars->offset_x = 0;
	vars->offset_y = 0;
	vars->shift_pressed = FALSE;
	vars->rot_x = 0;
	vars->rot_y = 0;
	vars->rot_z = 0;
	vars->projection = ISOMETRIC;
}

static int	setup_map_and_mlx(char *map_path, t_vars *vars)
{
	init_map(map_path, vars);
	if (!vars->map)
		return (MAP_ERROR);
	vars->mlx = mlx_init();
	if (vars->mlx == NULL)
		return (MLX_ERROR);
	return (OK);
}

void	init_map(char *path, t_vars *vars)
{
	if (!check_extension(path))
	{
		ft_error("Wrong file extension, should be .fdf file\n");
		return ;
	}
	extract_map_data(path, vars);
}

int	init_fdf(char *map_path, t_vars *vars)
{
	int	ret;

	init_vars(vars);
	ret = setup_map_and_mlx(map_path, vars);
	if (ret != OK)
		return (ret);
	if (!init_mlx_window(vars))
	{
		free_map(vars);
		destroy_mlx_display(vars);
		return (MLX_ERROR);
	}
	init_transform(vars);
	return (OK);
}
