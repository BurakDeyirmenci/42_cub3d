/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekarali <ekarali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:04:12 by ekarali           #+#    #+#             */
/*   Updated: 2023/06/07 14:46:52 by ekarali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_array(char **arr)
{
	int	i;

	i = -1;
	if (arr)
	{
		while (arr[++i])
			free(arr[i]);
		free(arr);
	}
}

char	*iterate_spaces(char *s)
{
	while (*s == ' ')
		s++;
	return (s);
}

char	*trim_ends(char *str)
{
	int	i;

	str = iterate_spaces(str);
	i = ft_strlen(str) - 1;
	while (str[i])
	{
		if (ft_isprint(str[i]) == 1 && (str[i] != 32
				&& !(str[i] >= 9 && str[i] <= 13)))
			break ;
		str[i] = 0;
		i--;
	}
	return (str);
}

char	*str_space(char *to_copy, int n)
{
	char	*str;
	int		i;

	str = (char *)ft_calloc(n + 3, sizeof(char));
	str = (char *)ft_memset(str, ' ', n + 2);
	i = -1;
	while (to_copy && to_copy[++i])
		str[i + 1] = to_copy[i];
	return (str);
}
