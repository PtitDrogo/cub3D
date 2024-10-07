/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfreydie <tfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:48:47 by lchapard          #+#    #+#             */
/*   Updated: 2024/10/07 15:05:50 by tfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_map_over(char **map, int index_past_line);
bool	is_there_invalid_empty_line(char **map);

int	check_outer_line(char **map, int height, int length)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < height)
	{
		if ((map[y][0] == '0') || (map[y][0] == 'D') ||
				(map[y][length - 1] == '0') ||
				(map[y][length - 1] == 'D'))
			return (1);
		else
			y++;
	}
	while (x < length - 1)
	{
		if ((map[0][x] == '0') || (map[0][x] == 'D') ||
				(map[height - 1][x] == '0') ||
				(map[height - 1][x] == 'D'))
			return (1);
		else
			x++;
	}
	return (0);
}

bool	invalid_neighbour(char **map, int x, int y)
{
	if (is_white_space(map[y][x - 1]))
		return (true);
	if (is_white_space(map[y][x + 1]))
		return (true);
	if (is_white_space(map[y - 1][x]))
		return (true);
	if (is_white_space(map[y + 1][x]))
		return (true);
	return (false);
}

int	check_inner_map(char **map, int height, int length)
{
	int	x;
	int	y;

	x = 1;
	y = 1;
	while (y < height - 1)
	{
		x = 1;
		while (x < length - 1)
		{
			if (map[y][x] == '0' || is_direction_c(map[y][x])
					|| map[y][x] == 'D')
			{
				if (invalid_neighbour(map, x, y))
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	unclosed_map(char **map, int height, int length)
{
	if (check_outer_line(map, height, length))
	{
		return (ERR_INVALID_CHAR_MAP);
	}
	if (check_inner_map(map, height, length))
	{
		return (ERR_INVALID_CHAR_MAP);
	}
	return (0);
}

bool	is_map_valid(t_info *w, char **m_map)
{
	int	m_height;
	int	m_length;
	int	err_code;

	if (is_there_invalid_empty_line(m_map) == true)
	{
		ft_printf2("Error\nEmpty line in map\n");
		return (false);
	}
	get_map_height(m_map, &m_height, &m_length);
	w->map_height = m_height;
	w->map_length = m_length;
	expand_map(m_map, m_length);
	err_code = invalid_player(m_map);
	if (!err_code)
		err_code = unclosed_map(m_map, m_height, m_length);
	if (err_code)
	{
		print_error_msg(err_code);
		return (false);
	}
	return (true);
}
