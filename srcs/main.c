/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 23:07:38 by vbronov           #+#    #+#             */
/*   Updated: 2024/12/27 03:24:12 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	init_mlx_window(t_vars *vars)
{
	mlx_get_screen_size(vars->mlx, &vars->screen_width, &vars->screen_height);
	vars->win = mlx_new_window(vars->mlx,
			vars->screen_width, vars->screen_height, TITLE);
	if (vars->win == NULL)
		return (FALSE);
	return (TRUE);
}

void	destroy_mlx_display(t_vars *vars)
{
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
}

// In MacOS mlx_loop never returns
int	main(int argc, char *argv[])
{
	t_vars	vars;
	int		ret;

	if (argc != 2)
	{
		ft_printf("Usage: %s <path_to_fdf_map>\n", argv[0]);
		return (ARG_ERROR);
	}
	ret = init_fdf(argv[1], &vars);
	if (ret != OK)
		return (ret);
	mlx_key_hook(vars.win, key_release, &vars);
	mlx_hook(vars.win, DESTROY_NOTIFY, 0, ft_close, &vars);
	mlx_loop_hook(vars.mlx, update_frame, &vars);
	mlx_loop(vars.mlx);
	destroy_mlx_display(&vars);
	return (OK);
}
