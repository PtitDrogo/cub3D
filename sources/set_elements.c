# include "cub3D.h"

void	setMapVectors(t_vector *vec, char c)
{
	if (c == 'N')
	{
		vec->xPos = 0;
		vec->yPos = 1;
		vec->xCam = 0.66;
		vec->yCam = 0;
	}
	if (c == 'S')
	{
		vec->xPos = 0;
		vec->yPos = -1;
		vec->xCam = -0.66;
		vec->yCam = 0;
	}
	if (c == 'W')
	{
		vec->xPos = -1;
		vec->yPos = 0;
		vec->xCam = 0;
		vec->yCam = 0.66;
	}
	if (c == 'E')
	{
		vec->xPos = 1;
		vec->yPos = 0;
		vec->xCam = 0;
		vec->yCam = -0.66;
	}
}

void	find_player(t_info *w)
{
	int	x;
	int	y;

	x = 1;
	y = 1;
	while (y < w->map_heigth - 1)
	{
		x = 1;
		while (x < w->map_lenght - 1)
		{
			if (is_direction_c(w->actual_map[y][x]))
			{
				w->vectors.x_pl = x;
				w->vectors.y_pl = y;
				setMapVectors(&w->vectors, w->map_file[y][x]);
				return ;
			}
			x++;
		}
		y++;
	}
}
