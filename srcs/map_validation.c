/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 13:11:11 by vbronov           #+#    #+#             */
/*   Updated: 2024/12/09 09:40:30 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	check_extension(char *file_name)
{
	int		len;
	char	*start;
	int		ext_len;

	ext_len = ft_strlen(FILE_EXT);
	len = ft_strlen(file_name);
	start = &file_name[len - ext_len];
	if (ft_strncmp(start, FILE_EXT, ext_len) == 0)
		return (TRUE);
	return (FALSE);
}

int	split_len(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
		i++;
	return (i);
}

int	parse_line(int **matrix, int idx, char **split, t_vars *vars)
{
	int		n;
	int		i;
	char	**z_and_color;

	n = split_len(split);
	if (vars->map_width == -1)
		vars->map_width = n;
	if (n != vars->map_width)
		return (ft_error("The map is not rectangular\n"));
	matrix[idx] = (int *)ft_calloc(n, sizeof(int));
	if (matrix[idx] == NULL)
		return (ft_error("parse_line calloc error\n"));
	i = 0;
	while (split[i] != NULL)
	{
		z_and_color = ft_split(split[i], ',');
		if (z_and_color == NULL)
			return (ft_error("z_and_color split error\n"));
		matrix[idx][i] = ft_atoi(z_and_color[0]);
		//TODO: add color
		// if (z_and_color[1])
		// 	vars->colors[i] = ft_atoi_base(z_and_color[1], 16);
		// else
		// 	vars->colors[i] = DEFAULT_COLOR;
		free_split(z_and_color);
		i++;
	}
	return (TRUE);
}
