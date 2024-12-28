/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 15:46:38 by vbronov           #+#    #+#             */
/*   Updated: 2024/12/27 04:14:59 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

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

int	interpolate_color(int color1, int color2, double fraction)
{
	t_coord	rgb1;
	t_coord	rgb2;
	t_coord	rgb;

	rgb1.x = (color1 >> 16) & 0xFF;
	rgb1.y = (color1 >> 8) & 0xFF;
	rgb1.z = color1 & 0xFF;
	rgb2.x = (color2 >> 16) & 0xFF;
	rgb2.y = (color2 >> 8) & 0xFF;
	rgb2.z = color2 & 0xFF;
	rgb.x = rgb1.x + (rgb2.x - rgb1.x) * fraction;
	rgb.y = rgb1.y + (rgb2.y - rgb1.y) * fraction;
	rgb.z = rgb1.z + (rgb2.z - rgb1.z) * fraction;
	return ((rgb.x << 16) | (rgb.y << 8) | rgb.z);
}
