/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarali <ekarali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 11:51:56 by ekarali           #+#    #+#             */
/*   Updated: 2023/06/15 11:52:37 by ekarali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_error_exit(t_err e, t_data *data, char *file, int c)
{
	if (!c)
		return (0);
	cub_end(data);
	if (e == end_game)
		exit(0);
	write(2, "Error\n", 7 * (e != end_game));
	write(2, "invalid number of arguments\n", 28 * (e == argc_err));
	write(2, "error reading file\n", 19 * (e == read_err));
	write(2, "file must be of .cub type\n", 26 * (e == extension_err));
	write(2, "error opening file: ", 20 * (e == file_err));
	ft_putendl_fd(file, 2);
	write(2, "file is empty\n", 14 * (e == empty_file));
	write(2, "invalid color\n", 14 * (e == color_err));
	write(2, "map not surrounded by walls\n", 28 * (e == wall_err));
	write(2, "invalid map\n", 12 * (e == map_err));
	write(2, "invalid character\n", 18 * (e == char_err));
	write(2, "invalid texture file\n", 21 * (e == texture_err));
	write(2, "invalid number of players\n", 26 * (e == player_err));
	write(2, "a problem with identifiers\n", 27 * (e == identifier_err));
	write(2, "test\n", 6 * (e == test));
	exit(1);
	return (1);
}

int	cub_exit(void *file)
{
	ft_error_exit(end_game, file, NULL, 1);
	return (0);
}

void	cub_end(t_data *g)
{
	if (!g)
		return ;
	free_array(g->map_data.map);
	free_array(g->square_map);
	if (g->fd > 0)
		close(g->fd);
	if (g->map_data.no)
		free(g->map_data.no);
	if (g->map_data.so)
		free(g->map_data.so);
	if (g->map_data.ea)
		free(g->map_data.ea);
	if (g->map_data.we)
		free(g->map_data.we);
	if (g->map_data.f)
		free(g->map_data.f);
	if (g->map_data.c)
		free(g->map_data.c);
	destroy_images(g);
}

void	destroy_images(t_data *g)
{
	if (g->tex.n && g->tex.n->i)
		free(g->tex.n->i);
	if (g->tex.s && g->tex.s->i)
		free(g->tex.s->i);
	if (g->tex.e && g->tex.e->i)
		free(g->tex.e->i);
	if (g->tex.w && g->tex.w->i)
		free(g->tex.w->i);
	if (g->win_img.i)
		mlx_destroy_image(g->mlx, g->win_img.i);
	if (g->window)
		mlx_destroy_window(g->mlx, g->window);
}
