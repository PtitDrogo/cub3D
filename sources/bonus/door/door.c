/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfreydie <tfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:44:59 by tfreydie          #+#    #+#             */
/*   Updated: 2024/10/07 13:56:42 by tfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	check_mid_ray(t_info *w);
static void	door_logic(t_info *w);
static void	update_animation_info(t_info *w, char type);

void	check_doors(t_info *w)
{
	dda_innit(w, DEFAULT_LENGTH / 2);
	movetoFirstXY(w, w->rayDirX, w->rayDirY);
	check_mid_ray(w);
	door_logic(w);
}

static void	door_logic(t_info *w)
{
	int	abs1;
	int	abs2;

	if (w->actual_map[w->y_strip][w->x_strip] == 'O' && !w->anim_playing)
	{
		abs1 = abs(w->y_strip - (int)w->y_pl);
		abs2 = abs(w->x_strip - (int)w->x_pl);
		if ((abs1 <= 1) && (abs2 <= 1) && (abs1 + abs2 > 0))
		{
			w->actual_map[w->y_strip][w->x_strip] = 'D';
			update_animation_info(w, 'c');
		}
	}
	else if (w->actual_map[w->y_strip][w->x_strip] == 'D' && !w->anim_playing)
	{
		abs1 = abs(w->y_strip - (int)w->y_pl);
		abs2 = abs(w->x_strip - (int)w->x_pl);
		if (abs1 <= 1 && abs2 <= 1)
		{
			w->actual_map[w->y_strip][w->x_strip] = 'O';
			update_animation_info(w, 'b');
		}
	}
}

static void	update_animation_info(t_info *w, char type)
{
	if (w->anim_playing == false)
	{
		w->anim_playing = true;
		w->anim_type = type;
		w->anim_frames = 11;
	}
	return ;
}

static void	check_mid_ray(t_info *w)
{
	while (42)
	{
		if (w->vectors.next_dist_x < w->vectors.next_dist_y)
		{
			w->vectors.next_dist_x += w->vectors.delta_x;
			w->current_map_x += w->vectors.step_x;
		}
		else
		{
			w->vectors.next_dist_y += w->vectors.delta_y;
			w->current_map_y += w->vectors.step_y;
		}
		if (w->actual_map[w->current_map_y][w->current_map_x] == '1')
			break ;
		if (w->actual_map[w->current_map_y][w->current_map_x] == 'D')
			break ;
		else if (w->actual_map[w->current_map_y][w->current_map_x] == 'O')
			break ;
	}
	w->x_strip = w->current_map_x;
	w->y_strip = w->current_map_y;
}
