/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 23:07:52 by vbronov           #+#    #+#             */
/*   Updated: 2024/12/27 04:15:04 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

// Dummy functions to prevent compilation error on MacOS
#ifdef __APPLE__

int	mlx_loop_end(void *mlx_ptr)
{
	(void)mlx_ptr;
	return (1);
}

int	mlx_destroy_display(void *mlx_ptr)
{
	(void)mlx_ptr;
	return (1);
}
#endif

static void	print_colors(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->map_height)
	{
		j = 0;
		while (j < vars->map_width)
		{
			ft_printf("%#x ", vars->colors[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

void	print_map(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->map_height)
	{
		j = 0;
		while (j < vars->map_width)
		{
			ft_printf("%d ", vars->map[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
	print_colors(vars);
}

int	ft_error(const char *msg)
{
	ft_printf("Error\n");
	ft_printf(msg);
	return (FALSE);
}
