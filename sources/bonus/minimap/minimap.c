/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfreydie <tfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:05:03 by tfreydie          #+#    #+#             */
/*   Updated: 2024/10/07 16:24:01 by tfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		get_color(t_info *w, int x, int y);
int		generate_square(t_info *w, float x, float y, int color);
void	show_player(t_info *w, float pixel_x, float pixel_y);

int	display_minimap(t_info *w)
{
	int		x;
	int		y;
	int		pixel_x;
	int		pixel_y;

	pixel_x = DEFAULT_LENGTH / w->map_length * 0.20;
	pixel_y = DEFAULT_HEIGHT / w->map_height * 0.20;
	y = 0;
	while (y < w->map_height)
	{
		x = 0;
		while (x < w->map_length)
		{
			generate_square(w, (x + MINIMAP_MARGIN) * pixel_x,
				(y + MINIMAP_MARGIN) * pixel_y, get_color(w, x, y));
			x++;
		}
		y++;
	}
	show_player(w, pixel_x, pixel_y);
	return (0);
}

int	generate_square(t_info *w, float x, float y, int color)
{
	int		i;
	int		j;
	float	pixel_x;
	float	pixel_y;

	pixel_x = DEFAULT_LENGTH / w->map_length * 0.20;
	pixel_y = DEFAULT_HEIGHT / w->map_height * 0.20;
	j = 0;
	while (j < pixel_y)
	{
		i = 0;
		while (i < pixel_x)
		{
			pixel_fill(&w->img_buffer, x + i, y + j, color);
			i++;
		}
		j++;
	}
	return (0);
}

int	get_color(t_info *w, int x, int y)
{
	char	c;

	c = w->actual_map[y][x];
	if (c == '0')
		return (0x694F8E);
	else if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (0x71);
	else if (is_white_space(c))
		return (0x005500);
	else if (c == 'D')
		return (0x582900);
	else if (c == 'O')
		return (0xd16100);
	else
		return (0xE3A5C7);
}

void	show_player(t_info *w, float pixel_x, float pixel_y)
{
	int	x;
	int	y;

	x = (int)w->x_pl + MINIMAP_MARGIN;
	y = (int)w->y_pl + MINIMAP_MARGIN;
	generate_square(w, x * pixel_x, y * pixel_y, 0xFFFFFFF);
}
