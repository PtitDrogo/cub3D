/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfreydie <tfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 20:31:29 by tfreydie          #+#    #+#             */
/*   Updated: 2024/10/07 12:25:15 by tfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_direction_c(char c)
{
	return (c == 'W' || c == 'E'
		|| c == 'N' || c == 'S');
}

bool	is_map_char(char c)
{
	return (c == '0' || c == '1'
		|| c == 'D'
		|| is_direction_c(c)
		|| c == '\v' || c == '\f'
		|| c == '\r' || c == ' '
		|| c == '\n' || c == '	');
}

bool	is_map_over(char **map, int index_past_line)
{
	int	i;

	i = 0;
	while (map[index_past_line])
	{
		while (map[index_past_line][i])
		{
			if (is_white_space(map[index_past_line][i]) == false)
				return (false);
			i++;
		}
		index_past_line++;
	}
	return (true);
}

bool	is_there_invalid_empty_line(char **map)
{
	int	i;
	int	j;

	j = 0;
	while (map[j])
	{
		i = 0;
		while (is_white_space(map[j][i]))
			i++;
		if (map[j][i] == '\0')
		{
			if (is_map_over(map, j + 1) == false)
				return (true);
		}
		j++;
	}
	return (false);
}

bool	contains_invalid_char(char *str, int *cpt)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_map_char(str[i]))
		{
			if (is_direction_c(str[i]))
				(*cpt) += 1;
			i++;
		}
		else
		{
			return (true);
		}
	}
	return (false);
}
