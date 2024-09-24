#include "cub3D.h"

//IDEA : I want to use the 2d map and just go through it and paint little cubes everytime theres a symbol;
//TO TRY : Just draw the thing on the entire screen then find a way to scale it down;
//
int	get_color(t_info *w, int x, int y);
int	generate_square(t_info *w, int x, int y, int color);

int display_minimap(t_info *w)
{
	// int map_x_start = DEFAULT_LENGTH * 0.5;
	// int map_y_start = DEFAULT_HEIGHT * 0.1;
	// int map_x_end   = map_x_start * 0.5;
	// int map_y_end   = map_y_start * 0.1;
	// int		square_x_size = DEFAULT_LENGTH / w->map_length; //(1920 / 24 or something)
	// int		square_y_size = DEFAULT_HEIGHT / w->map_height;

	int x;
	int y;

	printf("map height is %i\n", w->map_height);
	printf("map length is %i\n", w->map_length);

	y = 0;
	while (y < w->map_height)
	{
		x = 0;
		while (x < w->map_length)
		{
			pixel_fill(&w->img_buffer, DEFAULT_LENGTH / 2 + x, DEFAULT_HEIGHT / 2 + y, 0xFF0000);
			//generate square; from position x/y until size x of cube and size y of cube;
			// generate_square(w, x, y, get_color(w, x, y));
			x++;
		}      
		y++;
	}
	//Generate player;
	return (0);
}
//size of a square should be relative to the size of the screen
// x and y will be the coordinate of the position on the 2d map;
// I need to determinate the size of a square, how about map_height / 2dmap/heigth !; (then / by something else later for scaling ?)
// then x * square size gives me where the pixel is more or less
int	generate_square(t_info *w, int x, int y, int color)
{
	int			new_x;
	int			new_y;
	int			square_x_size = DEFAULT_LENGTH / w->map_length; //(1920 / 24 or something)
	int			square_y_size = DEFAULT_HEIGHT / w->map_height;
	int			end_y = y + square_y_size;
	int			end_x = x + square_x_size;

	if (end_x >= DEFAULT_LENGTH)
		end_x = DEFAULT_LENGTH -1;
	if (end_y >= DEFAULT_HEIGHT)
		end_y = DEFAULT_HEIGHT -1;

	new_y = y;
	while (new_y < end_y)
	{
		new_x = x;
		while (new_x < end_x)
		{
			pixel_fill(&w->img_buffer, x, y, color); // if this doesnt work switch i and j
			x++;
		}
		new_y++;
	}
	return (0);
}
int	get_color(t_info *w, int x, int y)
{
	//add door here later;
	char c;

	c = w->actual_map[y][x];
	if (c == '0')
		return (0x694F8E);
	else if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (0x71);
	else
		return (0xE3A5C7); //modify these colors later
}



//pixel_fill(&w->img_buffer, j, i, ceiling_color);
//x_pl is player x pos;
//y_pl is player y pos;