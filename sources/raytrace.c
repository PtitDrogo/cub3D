/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfreydie <tfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:43:33 by lchapard          #+#    #+#             */
/*   Updated: 2024/10/07 14:56:03 by tfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	goto_first_xy(t_info *w, double rayX, double rayY)
{
	if (rayX < 0)
	{
		w->vectors.step_x = -1;
		w->vectors.next_dist_x = (w->x_pl - w->current_map_x) * w->vectors.delta_x;
	}
	else
	{
		w->vectors.step_x = 1;
		w->vectors.next_dist_x = (w->current_map_x + 1.0 - w->x_pl) * w->vectors.delta_x;
	}
	if (rayY < 0)
	{
		w->vectors.step_y = -1;
		w->vectors.next_dist_y = (w->y_pl - w->current_map_y) * w->vectors.delta_y;
	}
	else
	{
		w->vectors.step_y = 1;
		w->vectors.next_dist_y = (w->current_map_y + 1.0 - w->y_pl) * w->vectors.delta_y;
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
		if(w->vectors.next_dist_x < w->vectors.next_dist_y)
		{
			w->vectors.next_dist_x += w->vectors.delta_x;
			w->current_map_x += w->vectors.step_x;
			w->side = 0;
		}
		else
		{
			w->vectors.next_dist_y += w->vectors.delta_y;
			w->current_map_y += w->vectors.step_y;
			w->side = 1;
		}
		if (is_special_block(w) == true)
			break ;
	}
	if(w->side == 0)
		wall_dist = (w->vectors.next_dist_x - w->vectors.delta_x);
	else
		wall_dist = (w->vectors.next_dist_y - w->vectors.delta_y);
	return (wall_dist);
}

void	get_drawlimits(t_info *w)
{
	w->line_height = (DEFAULT_HEIGHT / w->distwall);
	w->draw_start = DEFAULT_HEIGHT / 2 - w->line_height / 2;
	if (w->draw_start < 0)
		w->draw_start = 0;
	w->draw_end = w->line_height / 2 + DEFAULT_HEIGHT / 2;
	if (w->draw_end >= DEFAULT_HEIGHT)
		w->draw_end = DEFAULT_HEIGHT - 1;
}
