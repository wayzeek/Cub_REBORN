/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:30:46 by vcart             #+#    #+#             */
/*   Updated: 2023/06/14 18:29:05 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// Defines

# define SUCCESS 0
# define ERROR 1
# define WIN_WIDTH 1000
# define WIN_HEIGHT 1000
# define PI 3.14159265358979323846
# define MAP_SIZE 333
# define FOV 1.0471975512
# define SPEED 3

// Headers

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>

// Local headers

# include "../sources/libft/libft.h"
# include "../sources/minilibx-linux/mlx.h"

// Keycodes

typedef enum e_keycode
{
	W = 119,
	A = 97,
	S = 115,
	D = 100,
	O = 111,
	P = 112,
	R = 114,
	G = 103,
	B = 98,
	ESQ = 65307,
	TAB = 48,
	SPACE = 49,
	PLUS = 65451,
	MINUS = 65454,
	LEFT = 65361,
	RIGHT = 65363,
	DOWN = 65364,
	UP = 65362,
}	t_keycode;

// Point structure

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

// Image structure

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_point	size;
}	t_img;

// Parsing structure

typedef struct s_parsing
{
	t_img	texture_north;
	t_img	texture_south;
	t_img	texture_east;
	t_img	texture_west;

	int		color_floor;
	int		color_ceiling;

	int		map_fd;

	int		map_size_width;
	char	**map;
}	t_parsing;

// Vector structure

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

// Ray structure

typedef struct s_ray
{
	int			id;
	t_vector	start;
	t_vector	dir;
	t_vector	map;
	t_vector	deltadist;
	t_vector	step;
	t_vector	sidedist;
	t_point		hit;
	double		angle;
	double		length;
	char		last_incr;
	int			side_hit;

	int			boolean;

	t_img		*texture;
	int			x;
	int			lineheight;
	int			drawstart;
	int			drawend;
	double		wall_x;
	int			tex_x;
	double		tex_step;
	double		tex_pos;
}	t_ray;

// Player structure
typedef struct s_player
{
	t_point		pos;
	t_vector	dir;
	char		dir_char;
}	t_player;

// Data structure

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win;
	t_img		img;
	t_img		img_minimap;

	int			minimap_length;
	int			minimap_height;

	t_parsing	parsing;
	int			tile_size;
	t_player	player;
	double		angle_master;
	t_ray		ray_tab[WIN_WIDTH];
	int			max_ray_lenght;
}	t_data;

// main.c

int			main(int argc, char **argv);

// parsing.c

int			get_parsing(t_data *data, char *map_name);

// process.c

int			process_line(t_data *data, char *line, int map_size, int map_fd);

// check_error_colors.c

int			check_error_color(char *line);

// check_map_error.c

int			check_map_error(char **map);

// fill_colors.c

int			get_color(char	*line);

// fill_directions.c

char		*get_path(char *line);
int			fill_directions(t_data *data, char *line, int mode);

// fill_parsing.c

int			fill_floor_ceiling(t_data *data, char *line, int mode);
int			fill_directions(t_data *data, char *line, int mode);
int			fill_map(t_data *data, char *line, int map_size, int map_fd);
t_img		ft_new_sprite(void *mlx, char *path);
int			check_texture(t_img texture);

// free.c

void		free_tab(char **tab);
void		free_all(t_data *data);
void		free_and_exit(t_data *data);

// map_utils.c

int			get_len_longest_line(char	**map);
char		*complete_line(char	*str, int size);
char		**complete_map(char **map);
int			check_border(char *line);
int			line_is_closed(char *line);

// parsing_utils.c

void		init_parsing(t_data *data);
int			parsing_is_filled(t_data *data);
int			get_index_first_char(char *str);
int			check_extension(char *map_name);
int			is_empty_line(char *line);

// utils.c

int			get_map_size(char *map_name);
char		*remove_spaces(char *line);
int			len_tab(char **tab);
char		*remove_nl(char *line);

// init.c

int			init_all(t_data *data);
void		init_angle(t_data *data, int i);

// print.c

void		print_img(t_data *data);

// draw.c

void		mlx_pixel_put_img(t_img *img, int x, int y, int color);
void		put_tile(t_data *data, int x, int y, int color);
void		print_square(t_data *data, int x, int y, int size);
void		draw_stripe(t_data *data, t_ray *ray);
void		get_ray_texture(t_data *data, t_ray *ray);

// draw_utils.c

void		draw_segment(t_data *data, t_vector vec1, t_vector vec2, int color);
void		draw_seg(t_data *data, t_ray *ray);
void		floor_ceiling(t_data *data);
int			get_text_color(t_img *data, int x, int y);
void		calculate_length(t_data *data, t_ray *ray);

// hooks.c

int			key_hook(int keycode, t_data *data);
int			hook(void *mlx);

// raycasting.c

void		raycasting(t_data *data);

// utils.c

int			get_seg_length_squared(t_vector vec1, t_vector vec2);

#endif