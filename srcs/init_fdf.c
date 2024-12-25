/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 13:03:53 by vbronov           #+#    #+#             */
/*   Updated: 2024/12/14 20:11:49 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_vars(t_vars *vars)
{
	vars->mlx = NULL;
	vars->win = NULL;
	vars->map = NULL;
	vars->frame_count = 0;
	vars->last_measured_ms = 0;
	vars->map_height = -1;
	vars->map_width = -1;
	vars->screen_width = DEFAULT_SCREEN_WIDTH;
	vars->screen_height = DEFAULT_SCREEN_HEIGHT;
	vars->mousedown = 0;
	//TODO: check if default x and y are correct
	vars->mouse_x = 0;
	vars->mouse_y = 0;
}

void	init_map(char *path, t_vars *vars)
{
	if (!check_extension(path))
	{
		ft_error("Wrong file extension, should be .fdf file\n");
		return ;
	}
	vars->map = extract_map_data(path, vars);
	if (!vars->map)
	{
		free_map(vars);
		vars->map = NULL;
		return ;
	}
}

int	setup_map_and_mlx(char *map_path, t_vars *vars)
{
	init_map(map_path, vars);
	if (!vars->map)
		return (MAP_ERROR);
	vars->mlx = mlx_init();
	if (vars->mlx == NULL)
		return (MLX_ERROR);
	return (OK);
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
	return (OK);
}
