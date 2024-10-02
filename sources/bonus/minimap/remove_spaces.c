/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfreydie <tfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:50:58 by tfreydie          #+#    #+#             */
/*   Updated: 2024/10/01 18:53:48 by tfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	get_wall_dimension(char **map, int *max_len, int *max_height);
static void	trim_map(char **map, int max_len, int max_height);
static void	free_rest_of_map(char **rest_map);

void	remove_spaces(t_info *w)
{
	w->map_length = -1;
	w->map_height = -1;
	get_wall_dimension(w->actual_map, &w->map_length, &w->map_height);
	trim_map(w->actual_map, w->map_length, w->map_height);
	return ;
}

static void	get_wall_dimension(char **map, int *max_len, int *max_height)
{
	int	i;
	int	j;

	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] == '1')
			{
				if (i > *max_len)
					*max_len = i;
				if (j > *max_height)
					*max_height = j;
			}
			i++;
		}
		j++;
	}
	(*max_len)++;
	(*max_height)++;
}

static void	trim_map(char **map, int max_len, int max_height)
{
	int	j;

	j = 0;
	while (j < max_height)
	{
		map[j][max_len] = '\0';
		j++;
	}
	free_rest_of_map(&map[max_height]);
	map[max_height] = NULL;
	return ;
}

static void	free_rest_of_map(char **rest_map)
{
	int	i;

	if (rest_map == NULL)
		return ;
	i = 0;
	while (rest_map[i])
	{
		free(rest_map[i]);
		i++;
	}
}
