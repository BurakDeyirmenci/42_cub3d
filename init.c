/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdeyirme <rdeyirme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:37:03 by eda               #+#    #+#             */
/*   Updated: 2023/06/10 15:19:59 by rdeyirme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_data *data)
{
	data->map_data.longest = 0;
	data->map_data.line_count = 0;
	data->player.pos_x = 0;
	data->player.pos_y = 0;
	data->player.fov = 60;
	data->player.speed = 0.12f;
	data->window = NULL;
	ft_bzero(&data->win_img, sizeof(t_img));
	ft_bzero(&data->map_data, sizeof(t_map_data));
	nuller(data);
	data->player.direction = 0;
	data->mlx = mlx_init();
	data->tex.f = -1;
	data->tex.c = -1;
	data->mouse_x = 0;
}

void	nuller(t_data *data)
{
	data->map_data.map = NULL;
	data->square_map = NULL;
	data->map_data.no = NULL;
	data->map_data.so = NULL;
	data->map_data.ea = NULL;
	data->map_data.we = NULL;
	data->map_data.f = NULL;
	data->map_data.c = NULL;
	data->win_img.i = NULL;
	data->win_img.addr = NULL;
	data->tex.n = NULL;
	data->tex.s = NULL;
	data->tex.e = NULL;
	data->tex.w = NULL;
	data->player.p.w_pressed = 0;
	data->player.p.a_pressed = 0;
	data->player.p.s_pressed = 0;
	data->player.p.d_pressed = 0;
	data->player.p.left_pressed = 0;
	data->player.p.right_pressed = 0;
	data->ray.sin = 0;
	data->ray.cos = 0;
	data->ray.angle = 0;
}

void	init_game(t_data *data)
{
	data->window = mlx_new_window(data->mlx, WIDTH, HEIGHT, "penguen");
	data->win_img.i = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->win_img.addr = mlx_get_data_addr(data->win_img.i, &data->win_img.bpp, \
		&data->win_img.line_len, &data->win_img.endian);
	init_ray(data);
	mlx_hook(data->window, 02, 1L << 0, cub_keydown, data);
	mlx_hook(data->window, 03, 1L << 1, cub_keyup, data);
	mlx_hook(data->window, 17, 0, cub_exit, data);
	mlx_hook(data->window, 06, 1L << 6, cub_mouse, data);
	mlx_loop_hook(data->mlx, cub_update, data);
	mlx_loop(data->mlx);
}

void	init_textures(t_data *data)
{
	data->tex.n = mlx_load_img(data->mlx, data->map_data.no);
	data->tex.s = mlx_load_img(data->mlx, data->map_data.so);
	data->tex.e = mlx_load_img(data->mlx, data->map_data.ea);
	data->tex.w = mlx_load_img(data->mlx, data->map_data.we);
	if (!data->tex.n || !data->tex.s || !data->tex.e || !data->tex.w)
		ft_error_exit(texture_err, data, NULL, 1);
	if (data->tex.f == -1 || data->tex.c == -1)
		ft_error_exit(color_err, data, NULL, 1);
}

void	init_ray(t_data *g)
{
	g->ray.angle = 0;
	if (g->player.direction == 'S')
		g->ray.angle = 90;
	else if (g->player.direction == 'W')
		g->ray.angle = 180;
	else if (g->player.direction == 'N')
		g->ray.angle = 270;
	g->ray.hfov = g->player.fov / 2;
	g->ray.incre_angle = (float)g->player.fov / WIDTH;
	g->ray.precision = 125;
	g->ray.lim = 20;
}
