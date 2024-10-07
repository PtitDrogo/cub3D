/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:43:33 by lchapard          #+#    #+#             */
/*   Updated: 2024/10/07 13:43:35 by lchapard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	goto_first_xy(t_info *w, double rayX, double rayY)
{
	if (rayX < 0)
	{
		w->vectors.stepX = -1;
		w->vectors.nextDistX = (w->x_pl - w->current_map_x)
			* w->vectors.deltaX;
	}
	else
	{
		w->vectors.stepX = 1;
		w->vectors.nextDistX = (w->current_map_x + 1.0 - w->x_pl)
			* w->vectors.deltaX;
	}
	if (rayY < 0)
	{
		w->vectors.stepY = -1;
		w->vectors.nextDistY = (w->y_pl - w->current_map_y)
			* w->vectors.deltaY;
	}
	else
	{
		w->vectors.stepY = 1;
		w->vectors.nextDistY = (w->current_map_y + 1.0 - w->y_pl)
			* w->vectors.deltaY;
	}
}

bool	is_special_block(t_info *w)
{
	if (w->actual_map[w->current_map_y][w->current_map_x] == '1')
	{
		return (true);
	}
	if (w->actual_map[w->current_map_y][w->current_map_x] == 'D')
	{
		w->is_door = true;
		return (true);
	}
	return (false);
}

double	apply_dda(t_info *w, double wall_dist)
{
	w->is_door = false;
	while (42)
	{
		if (w->vectors.nextDistX < w->vectors.nextDistY)
		{
			w->vectors.nextDistX += w->vectors.deltaX;
			w->current_map_x += w->vectors.stepX;
			w->side = 0;
		}
		else
		{
			w->vectors.nextDistY += w->vectors.deltaY;
			w->current_map_y += w->vectors.stepY;
			w->side = 1;
		}
		if (is_special_block == true)
			break ;
	}
	if (w->side == 0)
		wall_dist = (w->vectors.nextDistX - w->vectors.deltaX);
	else
		wall_dist = (w->vectors.nextDistY - w->vectors.deltaY);
	return (wall_dist);
}

void	get_drawlimits(t_info *w)
{
	w->line_height = (DEFAULT_HEIGHT / w->distWall);
	w->draw_start = DEFAULT_HEIGHT / 2 - w->line_height / 2;
	if (w->draw_start < 0)
		w->draw_start = 0;
	w->draw_end = w->line_height / 2 + DEFAULT_HEIGHT / 2;
	if (w->draw_end >= DEFAULT_HEIGHT)
		w->draw_end = DEFAULT_HEIGHT - 1;
}
