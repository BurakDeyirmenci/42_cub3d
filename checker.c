/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdeyirme <rdeyirme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:12:57 by ekarali           #+#    #+#             */
/*   Updated: 2023/06/08 12:06:59 by rdeyirme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_map(t_data *data, char **map)
{
	int		i;
	int		j;
	char	c;

	i = -1;
	check_charerr(data, map);
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			c = map[i][j];
			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (map[i + 1][j] == ' ' || map[i][j + 1] == ' ' || map[i - 1] \
	[j] == ' ' || map[i][j - 1] == ' ' || map[i - 1][j - 1] == ' ' || map[i \
	- 1][j + 1] == ' ' || map[i + 1][j + 1] == ' ' || map[i + 1][j - 1] == ' ')
					ft_error_exit(wall_err, data, NULL, 1);
			}
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				check_direction(data, i, j);
		}
	}
}

void	check_charerr(t_data *data, char **map)
{
	int		i;
	int		j;
	char	c;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			c = map[i][j];
			if ((c != '0' && c != 'N' && c != 'S' && c != 'E'
					&& c != 'W' && c != '1' && c != ' '))
				ft_error_exit(char_err, data, NULL, 1);
		}
	}
}

void	check_direction(t_data *data, int i, int j)
{
	if (data->player.pos_x > 0 || data->player.pos_y > 0)
	{
		printf("cd::posx:%f posy:%f\n", data->player.pos_x, data->player.pos_y);
		ft_error_exit(player_err, data, NULL, 1);
	}
	data->player.pos_y = i;
	data->player.pos_x = j;
	data->player.direction = data->square_map[i][j];
}

char	*check_path(char *s, t_data *data)
{
	s = ft_strdup(trim_ends(s));
	if (open(s, O_RDONLY) == -1)
		ft_error_exit(texture_err, data, NULL, 1);
	return (s);
}

int	check_color_line(char **numbers)
{
	int		num;
	int		j;
	char	*n;

	j = -1;
	while (++j < 3 && numbers[j])
	{
		n = trim_ends(numbers[j]);
		num = 0;
		if (!n || !n[0])
			return (1);
		while (*n)
		{
			if (!ft_isdigit(*n))
				return (1);
			num = (*n - '0') + num * 10;
			n++;
		}
		if (num > 255)
			return (1);
	}
	if (numbers[j] || j != 3)
		return (1);
	return (0);
}
