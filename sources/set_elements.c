# include "cub3D.h"

void	setMapVectors(t_vector *vec, char c)
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
				setMapVectors(&w->vectors, w->actual_map[y][x]);
				w->actual_map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}
