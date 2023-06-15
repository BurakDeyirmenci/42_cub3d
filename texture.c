/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdeyirme <rdeyirme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:40:03 by eda               #+#    #+#             */
/*   Updated: 2023/06/08 18:13:50 by rdeyirme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_tex_color(t_data *g, t_img *i, int z)
{
	int	color;

	color = 0;
	if (g->square_map[(int)g->y][(int)g->x] == '1')
		color = my_mlx_pixel_get(i, (int)(i->width * (g->x + g->y)) \
			% i->width, z);
	return (color);
}

unsigned int	my_mlx_pixel_get(t_img *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	return (*(unsigned int *)dst);
}

t_img	*get_texture(t_data *g)
{
	t_img	*i;
	float	ray_cos;
	float	ray_sin;

	ray_cos = g->ray.cos;
	if (ray_cos < 0)
		ray_cos = -ray_cos;
	ray_sin = g->ray.sin;
	if (ray_sin < 0)
		ray_sin = -ray_sin;
	i = g->tex.n;
	if (g->square_map[(int)(g->y - ray_sin)][(int)g->x] != '1')
		i = g->tex.s;
	else if (g->square_map[(int)(g->y + ray_sin)][(int)g->x] != '1')
		i = g->tex.n;
	else if (g->square_map[(int)g->y][(int)(g->x + ray_cos)] != '1')
		i = g->tex.w;
	else if (g->square_map[(int)g->y][(int)(g->x - ray_cos)] != '1')
		i = g->tex.e;
	return (i);
}

void	draw_texture(t_data *g, t_img *i, int ray_count, int wall_height)
{
	float	dy;
	float	ds;
	float	cy[2];
	int		z;
	int		color;

	dy = ((float)wall_height * 2) / (float)i->height;
	ds = ((float)WIDTH / 2) - (float)wall_height;
	cy[1] = ds;
	z = -1;
	while (++z < i->height)
	{
		color = get_tex_color(g, i, z);
		cy[0] = cy[1];
		while (cy[0] < cy[1] + dy)
		{
			if (cy[0] >= 0 && cy[0] < (float)WIDTH)
				my_mlx_pixel_put(&g->win_img, ray_count, cy[0], color);
			cy[0]++;
		}
		cy[1] += dy;
	}
}

t_img	*mlx_load_img(void *ptr, char *path)
{
	int		fd;
	t_img	*i;

	i = malloc(sizeof(t_img));
	i->i = NULL;
	if (!path || ft_strncmp(&path[ft_strlen(path)-4], ".xpm", 4))
		return (i);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (i);
	close(fd);
	i->i = mlx_xpm_file_to_image(ptr, path, &i->width, &i->height);
	i->addr = mlx_get_data_addr(i->i, &i->bpp, &i->line_len, &i->endian);
	return (i);
}
