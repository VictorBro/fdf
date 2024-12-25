/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 22:56:57 by vbronov           #+#    #+#             */
/*   Updated: 2024/12/15 00:05:15 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <stdlib.h>
# include <unistd.h>//for close
# include <sys/time.h>
# include <time.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"

# define FALSE	0
# define TRUE	1
# define FRAME_RATE_MS 15
# define DEFAULT_COLOR 0x00FFFFFF
# define DEFAULT_SCREEN_WIDTH 1920
# define DEFAULT_SCREEN_HEIGHT 1080

# ifdef __linux__
#  define OS_LINUX		TRUE
#  define KEY_LEFT	 	65361
#  define KEY_RIGHT		65363
#  define KEY_DOWN		65364
#  define KEY_UP		65362
#  define KEY_ESC		65307
# elif __APPLE__
#  define OS_LINUX		FALSE
#  define KEY_LEFT		123
#  define KEY_RIGHT		124
#  define KEY_DOWN		125
#  define KEY_UP		126
#  define KEY_ESC		53
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
	int z;
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
	UP,
	DOWN,
	LEFT,
	RIGHT,
	DIRS,
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
	int			mousedown;
	int			mouse_x;
	int			mouse_y;
	void		*background;
	long long	last_measured_ms;
	int			frame_count;
	void		*mlx;
	void		*win;
	int			**map;
}						t_vars;

int			count_lines(int fd);
int			**extract_map_data(char *path, t_vars *vars);
void		free_map(t_vars *vars);
int			load_map_from_file(int **matrix, t_vars *vars, int fd);
void		free_matrix(int **matrix, int n);
void		free_split(char **split);
void		init_map(char *path, t_vars *vars);
int			ft_close(t_vars *vars);
int			check_extension(char *file_name);
int			ft_error(const char *msg);
void		ft_print_usage(char *prog_name);
void		init_vars(t_vars *vars);
int			key_release(int keycode, t_vars *vars);
int			key_press(int keycode, t_vars *vars);
int			mouse_press(int button, int x, int y, t_vars *vars);
int			mouse_release(int button, int x, int y, t_vars *vars);
int			mouse_move(int x, int y, t_vars *vars);
int			key_up_down(t_vars *vars, int commend);
int			key_left_right(t_vars *vars, int commend);
void		pixel_put(t_img *data, t_coord coord, int color, t_vars *vars);
void		draw_line(t_img *data, t_coord start, t_coord end, t_vars *vars);
int			update_frame(t_vars *vars);
int			init_mlx_window(t_vars *vars);
long long	current_time_ms(void);
int			init_fdf(char *map_path, t_vars *vars);
int			setup_map_and_mlx(char *map_path, t_vars *vars);
void		destroy_mlx_display(t_vars *vars);
int			parse_line(int **matrix, int idx, char **split, t_vars *vars);

# ifdef __APPLE__

int			mlx_loop_end(void *mlx_ptr);
int			mlx_destroy_display(void *mlx_ptr);
# endif

#endif