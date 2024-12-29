/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 22:56:57 by vbronov           #+#    #+#             */
/*   Updated: 2024/12/29 18:20:56 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H
# include <stdlib.h>
# include <unistd.h>//for close
# include <math.h>
# include "mlx.h"
# include "libft.h"

# define FALSE	0
# define TRUE	1
# define DEFAULT_COLOR 0x00FFFFFF
# define DEFAULT_SCREEN_WIDTH 1920
# define DEFAULT_SCREEN_HEIGHT 1080
# define DEFAULT_ZOOM 30.0
# define ZOOM_FACTOR 1.1
# define MIN_ZOOM_FACTOR 0.1 // Allow zoom out to 10% of initial
# define MAX_ZOOM_FACTOR 10.0 // Allow zoom in to 1000% of initial
# define PADDING 100 // Border padding in pixels
# define ROT_SPEED 0.01
# define ALTITUDE_FACTOR 0.1
# define TEXT_COLOR 0x00FFFFFF
# define MARGIN 20
# define HIGHLIGHT_COLOR 0x0000FF00

# ifdef __linux__
#  define OS_LINUX		TRUE
#  define KEY_DOWN			65364
#  define KEY_UP			65362
#  define KEY_ESC			65307
#  define KEY_SHIFT_LEFT	65505
#  define KEY_SHIFT_RIGHT	65506
#  define KEY_P				112
# elif __APPLE__
#  define OS_LINUX		FALSE
#  define KEY_DOWN			125
#  define KEY_UP			126
#  define KEY_ESC			53
#  define KEY_SHIFT_LEFT	257
#  define KEY_SHIFT_RIGHT	258
#  define KEY_P				35
# endif

# define MOUSE_PRESS	4
# define MOUSE_RELEASE	5
# define MOUSE_MOVE		6
# define KEY_PRESS		2
# define DESTROY_NOTIFY	17

# define TITLE "FDF"
# define FILE_EXT ".fdf"

typedef struct s_coord
{
	int	x;
	int	y;
	int	z;
}				t_coord;

enum
{
	OK,
	MLX_ERROR,
	ARG_ERROR,
	MAP_ERROR,
	ALLOC_ERROR,
};

enum
{
	ISOMETRIC,
	ORTHOGRAPHIC_FRONT,
	ORTHOGRAPHIC_SIDE,
	ORTHOGRAPHIC_TOP,
	PROJECTIONS,
};

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_vars
{
	int			map_height;
	int			map_width;
	int			screen_width;
	int			screen_height;
	int			mouse_pressed;
	int			mouse_x;
	int			mouse_y;
	void		*mlx;
	void		*win;
	int			**map;
	int			**colors;
	int			need_update;
	double		zoom;
	double		zoom_min;
	double		zoom_max;
	double		scale_altitude;
	int			offset_x;
	int			offset_y;
	int			shift_pressed;
	double		rot_x;
	double		rot_y;
	double		rot_z;
	char		projection;
}						t_vars;

void		extract_map_data(char *path, t_vars *vars);
void		free_map(t_vars *vars);
void		free_split(char **split);
void		init_map(char *path, t_vars *vars);
int			ft_close(t_vars *vars);
int			check_extension(char *file_name);
void		print_map(t_vars *vars);
int			ft_error(const char *msg);
int			key_release(int keycode, t_vars *vars);
int			key_press(int keycode, t_vars *vars);
int			mouse_press(int button, int x, int y, t_vars *vars);
int			mouse_release(int button, int x, int y, t_vars *vars);
int			mouse_move(int x, int y, t_vars *vars);
void		pixel_put(t_img *data, t_coord coord, int color, t_vars *vars);
int			interpolate_color(int color1, int color2, double fraction);
void		draw_line(t_img *data, t_coord start, t_coord end, t_vars *vars);
void		draw_map(t_vars *vars, t_img *frame);
int			update_frame(t_vars *vars);
int			init_mlx_window(t_vars *vars);
int			init_fdf(char *map_path, t_vars *vars);
void		destroy_mlx_display(t_vars *vars);
int			parse_line(int idx, char **split, t_vars *vars);
void		init_transform(t_vars *vars);
void		rotate_point(double *x, double *y, double *z, t_vars *vars);
void		project_point(t_vars *vars, t_coord a, t_coord *proj_a);

# ifdef __APPLE__

int			mlx_loop_end(void *mlx_ptr);
int			mlx_destroy_display(void *mlx_ptr);
# endif

#endif