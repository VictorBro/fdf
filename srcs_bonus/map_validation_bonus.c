/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 13:11:11 by vbronov           #+#    #+#             */
/*   Updated: 2024/12/27 04:14:55 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

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

int	ft_atoi_hex(const char *str)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	if (str && str[i] == '0' && (str[i + 1] == 'x' || str[i + 1] == 'X'))
		i += 2;
	while (str[i] != '\0')
	{
		if (str[i] >= 'A' && str[i] <= 'F')
			n = n * 16 + str[i] - 'A' + 10;
		else if (str[i] >= 'a' && str[i] <= 'f')
			n = n * 16 + str[i] - 'a' + 10;
		else if (str[i] >= '0' && str[i] <= '9')
			n = n * 16 + str[i] - '0';
		else
			break ;
		i++;
	}
	return (n);
}

static int	init_map_row(int idx, int width, t_vars *vars)
{
	vars->map[idx] = (int *)ft_calloc(width, sizeof(int));
	if (vars->map[idx] == NULL)
		return (ft_error("parse_line calloc for map error\n"));
	vars->colors[idx] = (int *)ft_calloc(width, sizeof(int));
	if (vars->colors[idx] == NULL)
		return (ft_error("parse_line calloc for color error\n"));
	return (TRUE);
}

int	parse_line(int idx, char **split, t_vars *vars)
{
	int		width;
	int		i;
	char	**z_and_color;

	width = split_len(split);
	if (vars->map_width == -1)
		vars->map_width = width;
	if (width != vars->map_width)
		return (ft_error("The map is not rectangular\n"));
	if (init_map_row(idx, width, vars) == FALSE)
		return (FALSE);
	i = 0;
	while (split[i] != NULL)
	{
		z_and_color = ft_split(split[i], ',');
		if (z_and_color == NULL)
			return (ft_error("z_and_color split error\n"));
		vars->map[idx][i] = ft_atoi(z_and_color[0]);
		vars->colors[idx][i] = DEFAULT_COLOR;
		if (z_and_color[1])
			vars->colors[idx][i] = ft_atoi_hex(z_and_color[1]);
		free_split(z_and_color);
		i++;
	}
	return (TRUE);
}
