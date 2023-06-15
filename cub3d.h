/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarali <ekarali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:19:42 by ekarali           #+#    #+#             */
/*   Updated: 2023/06/15 11:52:37 by ekarali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H
# include "./libft/libft.h"
# include "./gnl/get_next_line.h"
# include "printf/ft_printf.h"
# include "mlx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 600
# define HEIGHT WIDTH

typedef enum e_err
{
	end_game,
	argc_err,
	extension_err,
	file_err,
	empty_file,
	color_err,
	wall_err,
	map_err,
	char_err,
	player_err,
	texture_err,
	identifier_err,
	read_err,
	test
}				t_err;

typedef enum e_keys
{
	Key_W = 13,
	Key_A = 0,
	Key_S = 1,
	Key_D = 2,
	Key_ESC = 53,
	Key_up = 126,
	Key_down = 125,
	Key_left = 123,
	Key_right = 124
}					t_keys;

typedef struct s_pressed
{
	int	w_pressed;
	int	a_pressed;
	int	s_pressed;
	int	d_pressed;
	int	left_pressed;
	int	right_pressed;
}				t_pressed;

typedef struct s_player
{
	float		pos_x;
	float		pos_y;
	int			fov;
	char		direction;
	float		speed;
	t_pressed	p;
}				t_player;

typedef struct s_img
{
	int		height;
	int		width;
	void	*i;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_img;

typedef struct s_textures
{
	t_img	*n;
	t_img	*s;
	t_img	*e;
	t_img	*w;
	int		f;
	int		c;
}				t_textures;

typedef struct s_ray
{
	float	incre_angle;
	float	angle;
	float	cos;
	float	sin;
	float	hfov;
	float	lim;
	int		precision;
}				t_ray;

typedef struct s_map_data
{
	char	**map;
	int		line_count;
	int		longest;
	char	*no;
	char	*ea;
	char	*we;
	char	*so;
	char	*f;
	char	*c;
}				t_map_data;

typedef struct s_data
{
	int				fd;
	char			**square_map;
	void			*mlx;
	void			*window;
	t_img			win_img;
	t_player		player;
	int				mouse_x;
	t_textures		tex;
	t_ray			ray;
	t_map_data		map_data;
	float			x;
	float			y;
}				t_data;

// checker.c
void			error_check(t_data *data, char *path);
void			check_map(t_data *data, char **map);
void			check_direction(t_data *data, int i, int j);
char			*check_path(char *s, t_data *data);
int				check_color_line(char **numbers);
void			check_charerr(t_data *data, char **map);

// data.c
int				read_color_line(char *line, t_data *data, char c);
int				create_trgb(char **numbers);
void			create_map(t_data *data);
int				read_wall(char *line, t_data *data, char c);

// end.c
int				ft_error_exit(t_err e, t_data *data, char *file, int c);
int				cub_exit(void *file);
void			cub_end(t_data *g);
void			destroy_images(t_data *g);

// game.c
int				cub_keyup(int k, t_data *g);
int				cub_keydown(int k, t_data *data);
int				cub_mouse(int x, int y, t_data *g);
int				cub_update(void *param);
void			cub_raycast(t_data *g);

// init.c
void			init_data(t_data *data);
void			nuller(t_data *data);
void			init_game(t_data *data);
void			init_textures(t_data *data);
void			init_ray(t_data *g);

// main.c
int				main(int argc, char **argv);

// move.c
void			move_player(int k, t_data *data, float ray_cos, float ray_sin);
float			degree_to_radians(float degree);
float			distance_to_wall(t_data *g, float ray_angle);
void			cub_draw(t_data *g, int ray_count, float dis);
void			my_mlx_pixel_put(t_img *data, int x, int y, int color);

// reader.c
void			check_identifier(char *line, t_data *data, int *mic);
int				array_len(char **arr);
char			**extend_map(char **old_map, char *new_line);
void			read_content(t_data *data, int fd);

// texture.c
int				get_tex_color(t_data *g, t_img *i, int z);
unsigned int	my_mlx_pixel_get(t_img *data, int x, int y);
t_img			*get_texture(t_data *g);
void			draw_texture(t_data *g, t_img *i, int ray_count,
					int wall_height);
t_img			*mlx_load_img(void *ptr, char *path);

//utils.c
void			free_array(char **arr);
char			*iterate_spaces(char *s);
char			*trim_ends(char *str);
char			*str_space(char *to_copy, int n);

#endif
