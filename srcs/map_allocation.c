/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_allocation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 12:59:07 by vbronov           #+#    #+#             */
/*   Updated: 2024/12/09 09:39:48 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "fdf.h"

void	free_map(t_vars *vars)
{
	int	i;

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

void	free_matrix(int **matrix, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (matrix[i] == NULL)
			break ;
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	free(matrix);
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

int	load_map_from_file(int **matrix, t_vars *vars, int fd)
{
	int		i;
	char	*line;
	char	**split;

	i = 0;
	while (i < vars->map_height)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return (ft_error("Error reading the map file\n"));
		split = ft_split(line, ' ');
		free(line);
		if (!split)
			return (ft_error("Error splitting the map line\n"));
		if (!parse_line(matrix, i, split, vars))
		{
			free_split(split);
			return (FALSE);
		}
		free_split(split);
		i++;
	}
	return (TRUE);
}

int	**extract_map_data(char *path, t_vars *vars)
{
	int	**matrix;
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	vars->map_height = count_lines(fd);
	close(fd);
	matrix = (int **)ft_calloc((size_t)(vars->map_height), sizeof(int *));
	if (!matrix)
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		free(matrix);
		return (NULL);
	}
	if (load_map_from_file(matrix, vars, fd) == FALSE)
	{
		free_matrix(matrix, vars->map_height);
		matrix = NULL;
	}
	close(fd);
	return (matrix);
}
