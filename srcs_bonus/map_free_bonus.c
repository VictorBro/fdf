/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_free_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 12:59:07 by vbronov           #+#    #+#             */
/*   Updated: 2024/12/27 04:14:40 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	free_colors(t_vars *vars)
{
	int	i;

	if (vars->colors != NULL)
	{
		i = 0;
		while (i < vars->map_height)
		{
			if (vars->colors[i] == NULL)
				break ;
			free(vars->colors[i]);
			vars->colors[i] = NULL;
			i++;
		}
		free(vars->colors);
		vars->colors = NULL;
	}
}

void	free_map(t_vars *vars)
{
	int	i;

	if (vars->map != NULL)
	{
		i = 0;
		while (i < vars->map_height)
		{
			if (vars->map[i] == NULL)
				break ;
			free(vars->map[i]);
			vars->map[i] = NULL;
			i++;
		}
		free(vars->map);
		vars->map = NULL;
	}
	free_colors(vars);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
}
