/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfreydie <tfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 20:01:00 by tfreydie          #+#    #+#             */
/*   Updated: 2024/10/02 20:10:05 by tfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	transfer_parsing_data(t_info *w, t_parse *data)
{
	w->actual_map = &w->map_file[data->map_start];
	w->floor_v.r = data->floor_colors.r;
	w->floor_v.g = data->floor_colors.g;
	w->floor_v.b = data->floor_colors.b;
	w->ceiling_v.r = data->ceiling_colors.r;
	w->ceiling_v.g = data->ceiling_colors.g;
	w->ceiling_v.b = data->ceiling_colors.b;
}

int	count_lines(int cub_fd)
{
	char	*line;
	int		gnl_status;
	int		line_count;

	gnl_status = 0;
	line_count = 0;
	line = get_next_line_safe(cub_fd, &gnl_status);
	while (line)
	{
		line_count++;
		free(line);
		line = get_next_line_safe(cub_fd, &gnl_status);
	}
	if (gnl_status == 1)
		return (-1);
	return (line_count);
}

void	cub_check(const char *s)
{
	int	i;

	i = 0;
	if (ft_strlen(s) < 5)
		printf_exit("Error\nnot a .cub file\n");
	while (s[i])
		i++;
	i--;
	if (s[i] != 'b' || s[i - 1] != 'u' || s[i - 2] != 'c' || s[i - 3] != '.')
		printf_exit("Error\nnot a .cub file\n");
	return ;
}
