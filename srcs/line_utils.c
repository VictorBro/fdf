/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 15:46:38 by vbronov           #+#    #+#             */
/*   Updated: 2024/12/27 02:11:03 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * init_line_params - Initializes the parameters for drawing a line.
 */
static void	init_line_params(t_coord start, t_coord end,
			t_coord *delta, t_coord *step)
{
	delta->x = abs(end.x - start.x);
	delta->y = -abs(end.y - start.y);
	if (start.x < end.x)
		step->x = 1;
	else
		step->x = -1;
	if (start.y < end.y)
		step->y = 1;
	else
		step->y = -1;
}

/**
 * calc_line_step - Calculate current step parameters
 */
static void	calc_line_step(int *err, t_coord delta, t_coord step, t_coord *pos)
{
	int	e2;

	e2 = 2 * (*err);
	if (e2 >= delta.y)
	{
		*err += delta.y;
		pos->x += step.x;
	}
	if (e2 <= delta.x)
	{
		*err += delta.x;
		pos->y += step.y;
	}
}

static double	get_fraction(int total_steps, int curr_step)
{
	double	fraction;

	fraction = 1.0;
	if (total_steps > 0)
		fraction = (double)curr_step / total_steps;
	return (fraction);
}

/**
 * draw_line - Draws a line on an image using Bresenham's line algorithm.
 * @data: Pointer to the image data structure.
 * @start: The starting coordinate (x,y) and color value (z).
 * @end: The ending coordinate (x,y) and color value (z).
 * @vars: Pointer to additional variables or settings.
 *
 * This function uses Bresenham's line algorithm to draw a line between
 * two points. The z-component of start and end coordinates stores the
 * color values that will be interpolated along the line. The function
 * calculates pixel positions using the x,y coordinates and creates a gradient
 * between the start and end colors.
 */
void	draw_line(t_img *data, t_coord start, t_coord end, t_vars *vars)
{
	t_coord	delta;
	t_coord	step;
	int		err;
	int		total_steps;
	int		curr_step;

	init_line_params(start, end, &delta, &step);
	err = delta.x + delta.y;
	total_steps = fmax(delta.x, -delta.y);
	curr_step = 0;
	while (1)
	{
		pixel_put(data, start,
			interpolate_color(start.z, end.z,
				get_fraction(total_steps, curr_step)), vars);
		if (start.x == end.x && start.y == end.y)
			break ;
		calc_line_step(&err, delta, step, &start);
		curr_step++;
	}
}
