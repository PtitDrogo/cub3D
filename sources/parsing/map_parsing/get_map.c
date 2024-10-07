/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfreydie <tfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 20:15:51 by tfreydie          #+#    #+#             */
/*   Updated: 2024/10/02 20:30:03 by tfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	replace_endline(char **map);

char	**get_map_file2d(int cub_fd, int line_count)
{
	int		gnl_status;
	char	**map_file;
	int		i;

	i = 0;
	gnl_status = 0;
	map_file = ft_calloc(line_count + 1, sizeof(char *));
	if (map_file == NULL)
		return (NULL);
	while (i < line_count)
	{
		map_file[i] = get_next_line_safe(cub_fd, &gnl_status);
		if (gnl_status == 1)
			return (NULL);
		i++;
	}
	replace_endline(map_file);
	return (map_file);
}

static void	replace_endline(char **map)
{
	int	i;
	int	j;

	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] == '\n')
				map[j][i] = '\0';
			i++;
		}
		j++;
	}
	return ;
}
