/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdeyirme <rdeyirme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:47:50 by ekarali           #+#    #+#             */
/*   Updated: 2023/06/10 09:04:22 by rdeyirme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(int k, t_data *data, float ray_cos, float ray_sin)
{
	float	angle;

	angle = data->ray.angle;
	if (k == Key_A)
		angle = data->ray.angle - 90;
	else if (k == Key_S)
		angle = data->ray.angle - 180;
	else if (k == Key_D)
		angle = data->ray.angle + 90;
	ray_cos = cos(degree_to_radians(angle)) * data->player.speed;
	ray_sin = sin(degree_to_radians(angle)) * data->player.speed;
	if (data->square_map[(int)(data->player.pos_y + 0.5 + \
			(3 * ray_sin))][(int)(data->player.pos_x + 0.5)] != '1')
		data->player.pos_y += ray_sin;
	if (data->square_map[(int)(data->player.pos_y + 0.5)] \
			[(int)(data->player.pos_x + 0.5 + (3 * ray_cos))] != '1')
		data->player.pos_x += ray_cos;
}

float	degree_to_radians(float degree)
{
	return (degree * M_PI / 180);
}

float	distance_to_wall(t_data *g, float ray_angle)
{
	float	d;

	g->ray.cos = cos(degree_to_radians(ray_angle)) / g->ray.precision;
	g->ray.sin = sin(degree_to_radians(ray_angle)) / g->ray.precision;
	g->x = g->player.pos_x + 0.5;
	g->y = g->player.pos_y + 0.5;
	while (g->square_map[(int)g->y][(int)g->x] != '1' && \
		sqrt(powf(g->x - g->player.pos_x - 0.5, 2.) + \
		powf(g->y - g->player.pos_y - 0.5, 2.)) < g->ray.lim)
	{
		g->x += g->ray.cos;
		g->y += g->ray.sin;
	}
	d = sqrt(powf(g->x - g->player.pos_x - 0.5, 2.) + \
	powf(g->y - g->player.pos_y - 0.5, 2.));
	return (d * cos(degree_to_radians(ray_angle - g->ray.angle)));
}

void	cub_draw(t_data *g, int ray_count, float dis)
{
	int		wall_height;
	float	ds;
	int		j;

	wall_height = (int)(WIDTH / (2 * dis));
	ds = ((float)WIDTH / 2) - (float)wall_height;
	j = -1;
	while (++j < WIDTH)
	{
		if (j < ds)
			my_mlx_pixel_put(&g->win_img, ray_count, j, g->tex.c);
		else if (j >= ds)
			my_mlx_pixel_put(&g->win_img, ray_count, j, g->tex.f);
	}
	draw_texture(g, get_texture(g), ray_count, wall_height);
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}
