/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdeyirme <rdeyirme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:16:54 by ekarali           #+#    #+#             */
/*   Updated: 2023/06/08 18:14:59 by rdeyirme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub_keyup(int k, t_data *g)
{
	if (k == Key_left)
		g->player.p.left_pressed = 0;
	else if (k == Key_right)
		g->player.p.right_pressed = 0;
	else if (k == Key_W)
		g->player.p.w_pressed = 0;
	else if (k == Key_A)
		g->player.p.a_pressed = 0;
	else if (k == Key_S)
		g->player.p.s_pressed = 0;
	else if (k == Key_D)
		g->player.p.d_pressed = 0;
	return (0);
}

int	cub_keydown(int k, t_data *data)
{
	if (k == Key_ESC)
		ft_error_exit(end_game, data, NULL, 1);
	else if (k == Key_left)
		data->player.p.left_pressed = 1;
	else if (k == Key_right)
		data->player.p.right_pressed = 1;
	else if (k == Key_W)
		data->player.p.w_pressed = 1;
	else if (k == Key_A)
		data->player.p.a_pressed = 1;
	else if (k == Key_S)
		data->player.p.s_pressed = 1;
	else if (k == Key_D)
		data->player.p.d_pressed = 1;
	return (0);
}

int	cub_mouse(int x, int y, t_data *g)
{
	(void)y;
	g->ray.angle += (x - g->mouse_x) / 3;
	if (x > (g->mouse_x + 2) || x < (g->mouse_x - 2))
		g->mouse_x = x;
	return (0);
}

int	cub_update(void *param)
{
	t_data	*data;

	data = param;
	if (data->player.p.left_pressed)
		data->ray.angle -= 3;
	if (data->player.p.right_pressed)
		data->ray.angle += 3;
	if (data->player.p.w_pressed)
		move_player(Key_W, data, 0, 0);
	if (data->player.p.a_pressed)
		move_player(Key_A, data, 0, 0);
	if (data->player.p.s_pressed)
		move_player(Key_S, data, 0, 0);
	if (data->player.p.d_pressed)
		move_player(Key_D, data, 0, 0);
	cub_raycast(data);
	mlx_put_image_to_window(data->mlx, data->window, data->win_img.i, 0, 0);
	return (0);
}

void	cub_raycast(t_data *g)
{
	float	ray_angle;
	int		ray_count;
	float	dist;

	ray_angle = g->ray.angle - g->ray.hfov;
	ray_count = -1;
	while (++ray_count < WIDTH)
	{
		dist = distance_to_wall(g, ray_angle);
		cub_draw(g, ray_count, dist);
		ray_angle += g->ray.incre_angle;
	}
}
