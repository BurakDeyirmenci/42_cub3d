/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarali <ekarali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 21:30:57 by ekarali           #+#    #+#             */
/*   Updated: 2023/06/15 11:52:37 by ekarali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_check(t_data *data, char *path)
{
	if (ft_strlen(path) < 5 || ft_strncmp(&path[ft_strlen(path)-4], ".cub", 4))
		ft_error_exit(extension_err, NULL, NULL, 1);
	else if (path[ft_strlen(path)-5] == '/')
		ft_error_exit(extension_err, NULL, NULL, 1);
	data->fd = open(path, O_RDONLY);
	ft_error_exit(file_err, data, path, data->fd < 0);
	read_content(data, data->fd);
	create_map(data);
	check_map(data, data->square_map);
	if (!data->player.pos_x || !data->player.pos_y)
		ft_error_exit(player_err, NULL, NULL, 1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	ft_error_exit(argc_err, NULL, NULL, argc != 2);
	init_data(&data);
	error_check(&data, argv[1]);
	init_textures(&data);
	init_game(&data);
}
