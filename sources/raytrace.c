#include "cub3D.h"

void	movetoFirstXY(t_info *w, double rayX, double rayY)
{
	if(rayX < 0)
	{
		w->vectors.stepX = -1;
		w->vectors.nextDistX = (w->x_pl - w->current_map_x) * w->vectors.deltaX;
	}
	else
	{
		w->vectors.stepX = 1;
		w->vectors.nextDistX = (w->current_map_x + 1.0 - w->x_pl) * w->vectors.deltaX;
	}
	if(rayY < 0)
	{
		w->vectors.stepY = -1;
		w->vectors.nextDistY = (w->y_pl - w->current_map_y) * w->vectors.deltaY;
	}
	else
	{
		w->vectors.stepY = 1;
		w->vectors.nextDistY = (w->current_map_y + 1.0 - w->y_pl) * w->vectors.deltaY;
	}
}

double	applyDDA(t_info *w, double wall_dist, int i)
{
	w->is_door = false;
	w->OpDoorFound  = false; 
	while(42)
	{
		if(w->vectors.nextDistX < w->vectors.nextDistY)
		{
			w->vectors.nextDistX += w->vectors.deltaX;
			w->current_map_x += w->vectors.stepX;
			w->side = 0;
			// print_map_current(w->actual_map, w->current_map_x, w->current_map_y);
		}
		else
		{
			w->vectors.nextDistY += w->vectors.deltaY;
			w->current_map_y += w->vectors.stepY;
			w->side = 1;
			// print_map_current(w->actual_map, w->current_map_x, w->current_map_y);
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
		if(w->actual_map[w->current_map_y][w->current_map_x] == 'O')
		{
			if (!w->OpDoorFound && i == DEFAULT_LENGTH / 2)
			{
				w->x_strip2 = w->current_map_x;
				w->y_strip2 = w->current_map_y;
				w->OpDoorFound = true;
			}
		}
	}
	if (i == DEFAULT_LENGTH / 2)
	{
		w->x_strip = w->current_map_x;
		w->y_strip = w->current_map_y;
	}
	if(w->side == 0)
		wall_dist = (w->vectors.nextDistX - w->vectors.deltaX);
	else
		wall_dist = (w->vectors.nextDistY - w->vectors.deltaY);
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
