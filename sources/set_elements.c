/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfreydie <tfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:13:03 by tfreydie          #+#    #+#             */
/*   Updated: 2024/10/07 13:16:38 by tfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	set_vertical(t_vector *vec, char c);
static void	set_horizontal(t_vector *vec, char c);

void	set_map_vectors(t_vector *vec, char c)
{
	set_vertical(vec, c);
	set_horizontal(vec, c);
}

static void	set_vertical(t_vector *vec, char c)
{
	if (c == 'N')
	{
		vec->xPos = 0.0;
		vec->yPos = -1.0;
		vec->xCam = 0.66;
		vec->yCam = 0.0;
	}
	if (c == 'S')
	{
		vec->xPos = 0.0;
		vec->yPos = 1.0;
		vec->xCam = -0.66;
		vec->yCam = 0.0;
	}
	return ;
}

static void	set_horizontal(t_vector *vec, char c)
{
	if (c == 'W')
	{
		vec->xPos = -1.0;
		vec->yPos = 0.0;
		vec->xCam = 0.0;
		vec->yCam = -0.66;
	}
	if (c == 'E')
	{
		vec->xPos = 1.0;
		vec->yPos = 0.0;
		vec->xCam = 0.0;
		vec->yCam = 0.66;
	}
	return ;
}

void	find_player(t_info *w)
{
	int	x;
	int	y;

	x = 1;
	y = 1;
	while (y < w->map_height - 1)
	{
		x = 1;
		while (x < w->map_length - 1)
		{
			if (is_direction_c(w->actual_map[y][x]))
			{
				w->x_pl = x + 0.5;
				w->y_pl = y + 0.5;
				set_map_vectors(&w->vectors, w->actual_map[y][x]);
				w->actual_map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}
