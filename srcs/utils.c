/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 23:07:52 by vbronov           #+#    #+#             */
/*   Updated: 2024/12/08 17:40:25 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

long long	current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL));
}

int	count_lines(int fd)
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

int	ft_error(const char *msg)
{
	ft_printf("Error\n");
	ft_printf(msg);
	return (FALSE);
}
