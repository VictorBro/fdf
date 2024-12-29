/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_update_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 20:23:51 by vbronov           #+#    #+#             */
/*   Updated: 2024/12/29 18:21:49 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h" 

static void	draw_projections_menu(t_vars *vars, int *y)
{
	int	color;

	mlx_string_put(vars->mlx, vars->win, MARGIN + 10, *y, TEXT_COLOR,
		"Projections:");
	*y += 20;
	color = TEXT_COLOR;
	if (vars->projection == ISOMETRIC)
		color = HIGHLIGHT_COLOR;
	mlx_string_put(vars->mlx, vars->win, MARGIN + 20, *y, color, "Isometric");
	*y += 20;
	color = TEXT_COLOR;
	if (vars->projection == ORTHOGRAPHIC_FRONT)
		color = HIGHLIGHT_COLOR;
	mlx_string_put(vars->mlx, vars->win, MARGIN + 20, *y, color, "Front View");
	*y += 20;
	color = TEXT_COLOR;
	if (vars->projection == ORTHOGRAPHIC_SIDE)
		color = HIGHLIGHT_COLOR;
	mlx_string_put(vars->mlx, vars->win, MARGIN + 20, *y, color, "Side View");
	*y += 20;
	color = TEXT_COLOR;
	if (vars->projection == ORTHOGRAPHIC_TOP)
		color = HIGHLIGHT_COLOR;
	mlx_string_put(vars->mlx, vars->win, MARGIN + 20, *y, color, "Top View");
	*y += 20;
}

static void	draw_instructions(t_vars *vars)
{
	int	y;

	y = MARGIN;
	mlx_string_put(vars->mlx, vars->win, MARGIN, y, TEXT_COLOR,
		"Controls:");
	y += 20;
	mlx_string_put(vars->mlx, vars->win, MARGIN, y, TEXT_COLOR,
		"Mouse drag - Move map");
	y += 20;
	mlx_string_put(vars->mlx, vars->win, MARGIN, y, TEXT_COLOR,
		"Shift + drag - Rotate");
	y += 20;
	mlx_string_put(vars->mlx, vars->win, MARGIN, y, TEXT_COLOR,
		"Mouse wheel - Zoom in/out");
	y += 20;
	mlx_string_put(vars->mlx, vars->win, MARGIN, y, TEXT_COLOR,
		"Up/Down - Change altitude");
	y += 20;
	mlx_string_put(vars->mlx, vars->win, MARGIN, y, TEXT_COLOR,
		"P - Change projection");
	y += 20;
	draw_projections_menu(vars, &y);
	y += 20;
	mlx_string_put(vars->mlx, vars->win, MARGIN, y, TEXT_COLOR,
		"ESC - Exit");
}

int	update_frame(t_vars *vars)
{
	t_img	frame;

	if (vars->need_update == FALSE || vars->mlx == NULL)
		return (OK);
	frame.img = mlx_new_image(vars->mlx,
			vars->screen_width, vars->screen_height);
	if (frame.img == NULL)
		return (OK);
	frame.addr = mlx_get_data_addr(frame.img, &frame.bits_per_pixel,
			&frame.line_length, &frame.endian);
	if (frame.addr == NULL)
	{
		mlx_destroy_image(vars->mlx, frame.img);
		return (OK);
	}
	draw_map(vars, &frame);
	mlx_put_image_to_window(vars->mlx, vars->win, frame.img, 0, 0);
	draw_instructions(vars);
	mlx_destroy_image(vars->mlx, frame.img);
	vars->need_update = FALSE;
	return (OK);
}
