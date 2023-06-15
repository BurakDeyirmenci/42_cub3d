/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdeyirme <rdeyirme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 21:05:58 by ekarali           #+#    #+#             */
/*   Updated: 2023/06/10 09:34:44 by rdeyirme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	read_wall(char *line, t_data *data, char c)
{
	if (c == 'N' && !data->map_data.no)
		data->map_data.no = check_path(&line[3], data);
	else if (c == 'S' && !data->map_data.so)
		data->map_data.so = check_path(&line[3], data);
	else if (c == 'E' && !data->map_data.ea)
		data->map_data.ea = check_path(&line[3], data);
	else if (c == 'W' && !data->map_data.we)
		data->map_data.we = check_path(&line[3], data);
	else
		ft_error_exit(identifier_err, data, NULL, 1);
	return (0);
}

int	read_color_line(char *line, t_data *data, char c)
{
	int		err;
	char	**numbers;

	err = 0;
	if (c == 'F')
	{
		data->map_data.f = ft_strdup(trim_ends(line));
		numbers = ft_split(data->map_data.f + 1, ',');
		err += check_color_line(numbers);
		if (!err)
			data->tex.f = create_trgb(numbers);
		free_array(numbers);
	}
	else if (c == 'C')
	{
		data->map_data.c = ft_strdup(trim_ends(line));
		numbers = ft_split(data->map_data.c + 1, ',');
		err += check_color_line(numbers);
		if (!err)
			data->tex.c = create_trgb(numbers);
		free_array(numbers);
	}
	return (err);
}

int	create_trgb(char **numbers)
{
	return (ft_atoi(numbers[0]) << 16
		| ft_atoi(numbers[1]) << 8
		| ft_atoi(numbers[2]));
}

void	create_map(t_data *data)
{
	char	*first_line;
	int		i;

	data->square_map = malloc(sizeof(char *) * (data->map_data.line_count + 3));
	data->square_map[data->map_data.line_count + 2] = NULL;
	first_line = str_space(NULL, data->map_data.longest);
	data->square_map[0] = first_line;
	data->square_map[data->map_data.line_count + 1] = ft_strdup(first_line);
	if (data->map_data.map && data->map_data.map[0])
	{
		i = -1;
		while (data->map_data.map[++i])
			data->square_map[i + 1] = str_space(data->map_data.map[i], \
			data->map_data.longest);
	}
}
