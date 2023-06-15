/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eda <eda@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 21:07:09 by ekarali           #+#    #+#             */
/*   Updated: 2023/06/03 21:59:58 by eda              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_identifier(char *line, t_data *data, int *mic)
{
	line = iterate_spaces(line);
	if (!ft_strncmp(line, "SO", 2) || !ft_strncmp(line, "NO", 2)
		|| !ft_strncmp(line, "EA", 2) || !ft_strncmp(line, "WE", 2))
		read_wall(line, data, line[0]);
	else if (!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1))
		ft_error_exit(color_err, data, NULL,
			read_color_line(line, data, line[0]));
	else if (line[0] == '\0' || line[0] == '\n')
		(*mic)--;
	(*mic)++;
	data->map_data.line_count--;
}

int	array_len(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

char	**extend_map(char **old_map, char *new_line)
{
	char	**new_map;
	int		len;
	int		i;

	i = -1;
	new_map = NULL;
	len = array_len(old_map);
	new_map = malloc(sizeof(char *) * (len + 2));
	if (!new_map)
		return (old_map);
	new_map[len + 1] = NULL;
	while (++i < len)
	{
		new_map[i] = ft_strdup(old_map[i]);
		if (!new_map[i])
		{
			free_array(old_map);
			free_array(new_map);
		}
	}
	new_map[i] = ft_strdup(new_line);
	free_array(old_map);
	return (new_map);
}

void	read_content(t_data *data, int fd)
{
	char	*line[2];
	int		mic;

	mic = 0;
	while (1)
	{
		line[0] = get_next_line(fd);
		if (!line[0])
			break ;
		data->map_data.line_count++;
		line[1] = ft_strtrim(line[0], "\n");
		free (line[0]);
		if (line[1] && mic < 6)
			check_identifier(line[1], data, &mic);
		else
			data->map_data.map = extend_map(data->map_data.map, line[1]);
		if ((int)ft_strlen(line[1]) > data->map_data.longest)
			data->map_data.longest = ft_strlen(line[1]);
		free(line[1]);
	}
	if (!data->map_data.no || !data->map_data.so || !data->map_data.ea
		|| !data->map_data.we || !data->map_data.f || !data->map_data.c)
		ft_error_exit(identifier_err, data, NULL, 1);
}
