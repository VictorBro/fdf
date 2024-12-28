/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_allocation_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 12:59:07 by vbronov           #+#    #+#             */
/*   Updated: 2024/12/27 04:16:41 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include "fdf_bonus.h"

static int	process_line(char *line, int idx, t_vars *vars)
{
	char	*trimmed_line;
	char	**split;
	int		result;

	trimmed_line = ft_strtrim(line, " \n");
	if (!trimmed_line)
		return (ft_error("Error trimming the map line\n"));
	split = ft_split(trimmed_line, ' ');
	free(trimmed_line);
	if (!split)
		return (ft_error("Error splitting the map line\n"));
	result = parse_line(idx, split, vars);
	free_split(split);
	return (result);
}

static int	load_map_from_file(t_vars *vars, int fd)
{
	int		i;
	char	*line;
	int		result;

	i = 0;
	while (i < vars->map_height)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return (ft_error("Error reading the map file\n"));
		result = process_line(line, i, vars);
		free(line);
		if (!result)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int	count_lines(int fd)
{
	int		counter;
	char	*line;

	counter = 0;
	line = get_next_line(fd);
	while (line)
	{
		counter++;
		free(line);
		line = get_next_line(fd);
	}
	return (counter);
}

void	extract_map_data(char *path, t_vars *vars)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (perror("Error opening the map file"));
	vars->map_height = count_lines(fd);
	close(fd);
	vars->map = (int **)ft_calloc((size_t)(vars->map_height), sizeof(int *));
	if (!vars->map)
		return (perror("Error allocating memory for the map"));
	vars->colors = (int **)ft_calloc((size_t)(vars->map_height), sizeof(int *));
	if (!vars->colors)
	{
		perror("Error allocating memory for the colors");
		return (free_map(vars));
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening the map file");
		return (free_map(vars));
	}
	if (load_map_from_file(vars, fd) == FALSE)
		free_map(vars);
	close(fd);
}
