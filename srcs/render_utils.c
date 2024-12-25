/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 15:46:38 by vbronov           #+#    #+#             */
/*   Updated: 2024/12/14 23:17:00 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * pixel_put - Puts a pixel of a specified color at a given coordinate on
 * an image.
 * @data: Pointer to the image structure.
 * @coord: Coordinate structure containing the x and y positions.
 * @color: The color of the pixel to be put.
 * @vars: Pointer to the structure containing various parameters including 
 * 	screen dimensions and mlx instance.
 *
 * This function checks if the given coordinates are within the screen
 * boundaries.
 * If the coordinates are valid, it calculates the destination address
 * in the image data and sets the pixel color. The color value is adjusted
 * based on the image's bits per pixel and endian format.
 * endian = 0 means little endian, the LSB (Blue) is stored first.
 * endian = 1 means big endian, the MSB (Alpha) is stored first.
 */
void	pixel_put(t_img *data, t_coord coord, int color, t_vars *vars)
{
	char	*dst;

	if (coord.x < 0 || coord.x >= vars->screen_width
		|| coord.y < 0 || coord.y >= vars->screen_height)
		return ;
	if (data->bits_per_pixel != 32)
		color = mlx_get_color_value(vars->mlx, color);
	dst = data->addr + (coord.y * data->line_length
			+ coord.x * (data->bits_per_pixel / 8));
	if (data->endian == 0)
		*(unsigned int *)dst = color;
	else
	{
		*(unsigned int *)dst = (color & 0xFF000000)
			| ((color & 0x00FF0000) >> 8)
			| ((color & 0x0000FF00) << 8)
			| ((color & 0x000000FF) << 24);
	}
}

void	ft_print_usage(char *prog_name)
{
	ft_printf("Usage: %s <path_to_fdf_map>\n", prog_name);
}

/**
 * draw_line - Draws a line on an image using Bresenham's line algorithm.
 * @data: Pointer to the image data structure.
 * @start: The starting coordinate of the line.
 * @end: The ending coordinate of the line.
 * @vars: Pointer to additional variables or settings.
 *
 * This function uses Bresenham's line algorithm to draw a line from the
 * starting coordinate to the ending coordinate on the given image. It
 * calculates the differences and steps for the x and y coordinates and
 * iteratively sets the pixels along the line path.
 */
void	draw_line(t_img *data, t_coord start, t_coord end, t_vars *vars)
{
	t_coord	delta;
	t_coord	step;
	int		err;
	int		e2;

	delta.x = abs(end.x - start.x);
	step.x = -1;
	if (start.x < end.x)
		step.x = 1;
	delta.y = -abs(end.y - start.y);
	step.y = -1;
	if (start.y < end.y)
		step.y = 1;
	err = delta.x + delta.y;
	while (1)
	{
		pixel_put(data, start, 0x00FFFFFF, vars);
		if (start.x == end.x && start.y == end.y)
			break ;
		e2 = 2 * err;
		if (e2 >= delta.y)
		{
			err += delta.y;
			start.x += step.x;
		}
		if (e2 <= delta.x)
		{
			err += delta.x;
			start.y += step.y;
		}
	}
}
