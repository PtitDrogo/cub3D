#include "cub3D.h"

static void	checkMidRay(t_info *w);

void	check_doors(t_info *w)
{
	int	abs1;
	int	abs2;

	dda_innit(w, DEFAULT_LENGTH / 2);
	movetoFirstXY(w, w->rayDirX, w->rayDirY);
	checkMidRay(w);

	if (w->actual_map[w->y_strip][w->x_strip] == 'O' && w->anim_playing == false)
	{
		abs1 = abs(w->y_strip - (int)w->y_pl);
		abs2 = abs(w->x_strip - (int)w->x_pl);
		if (( abs1 <= 1) && (abs2 <= 1) && (abs1 + abs2 > 0))
		{
			w->actual_map[w->y_strip][w->x_strip] = 'D';
			if (w->anim_playing == false)
			{
				w->anim_playing = true;
				w->anim_type = 'c';
				w->anim_frames = 11; //this can change;
			}
		}
	}
	else if (w->actual_map[w->y_strip][w->x_strip] == 'D' && w->anim_playing == false)
	{
		if (abs(w->y_strip - (int)w->y_pl) <= 1 && abs(w->x_strip - (int)w->x_pl) <= 1)
		{
			w->actual_map[w->y_strip][w->x_strip] = 'O';
		if (w->anim_playing == false)
		{
			w->anim_playing = true;
			w->anim_type ='b';
			w->anim_frames = 11; //this can change;
		}
		}
	}
}

static void	checkMidRay(t_info *w)
{
	while(42)
	{
		if(w->vectors.nextDistX < w->vectors.nextDistY)
		{
			w->vectors.nextDistX += w->vectors.deltaX;
			w->current_map_x += w->vectors.stepX;
		}
		else
		{
			w->vectors.nextDistY += w->vectors.deltaY;
			w->current_map_y += w->vectors.stepY;
		}
		if(w->actual_map[w->current_map_y][w->current_map_x] == '1')
			break;
		if(w->actual_map[w->current_map_y][w->current_map_x] == 'D')
			break;
		else if(w->actual_map[w->current_map_y][w->current_map_x] == 'O')
			break ;
	}
	w->x_strip = w->current_map_x;
	w->y_strip = w->current_map_y;
}
