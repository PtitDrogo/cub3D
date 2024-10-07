#include "cub3D.h"

void	movetoFirstXY(t_info *w, double rayX, double rayY)
{
	if(rayX < 0)
	{
		w->vectors.step_x = -1;
		w->vectors.next_dist_x = (w->x_pl - w->current_map_x) * w->vectors.delta_x;
	}
	else
	{
		w->vectors.step_x = 1;
		w->vectors.next_dist_x = (w->current_map_x + 1.0 - w->x_pl) * w->vectors.delta_x;
	}
	if(rayY < 0)
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

double	applyDDA(t_info *w, double wall_dist)
{
	w->is_door = false;
	while(42)
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
		if(w->actual_map[w->current_map_y][w->current_map_x] == '1')
		{
			break;
		}
		if(w->actual_map[w->current_map_y][w->current_map_x] == 'D')
		{
			w->is_door = true;
			break;
		}
	}
	if(w->side == 0)
		wall_dist = (w->vectors.next_dist_x - w->vectors.delta_x);
	else
		wall_dist = (w->vectors.next_dist_y - w->vectors.delta_y);
	return (wall_dist);
}

void	getDrawLimits(t_info *w)
{
	w->line_height = (DEFAULT_HEIGHT / w->distWall); //BUG Distwall can be 0 and it crashes stuff
	// printf("distwall : %f\n",  w->distWall);
	//calculate lowest and highest pixel to fill in current stripe
	// w->draw_start = -w->line_height / 2 + DEFAULT_HEIGHT / 2;
	w->draw_start = DEFAULT_HEIGHT / 2 - w->line_height / 2;
	if(w->draw_start < 0)
		w->draw_start = 0;
	w->draw_end = w->line_height / 2 + DEFAULT_HEIGHT / 2;
	if(w->draw_end >= DEFAULT_HEIGHT)
		w->draw_end = DEFAULT_HEIGHT - 1;
	//Idk this entire thing gets the limits of where to draw the cubes somehow man
}
