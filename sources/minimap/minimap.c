#include "cub3D.h"


int display_minimap(t_info *w)
{
	char **map;
	static int map_x_start = DEFAULT_LENGTH * 0.5;
	static int map_y_start = DEFAULT_HEIGHT * 0.1;
	int x;
	int y;

	y = 0;
	map = w->actual_map;
	while (y < w->map_heigth)
	{
		x = 0;
		while (x < w->map_length)
		{
			//generate square;
			x++;
		}      
		y++;
	}
	return (0);
}
//size of a square should be relative to the size of the screen
int	generate_square(t_info *w, int x, int y)
{
	w->img_buffer;
	pixel_fill();

}

//x_pl is player x pos;
//y_pl is player y pos;