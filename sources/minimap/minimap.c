#include "cub3D.h"

#define PIXEL 10
#define SCALE 0.001
//IDEA : what if I just do a calculation and if there isnt enough space i just dont show the minimap;

int		get_color(t_info *w, int x, int y);
int		generate_square(t_info *w, int x, int y, int color);
void	show_player(t_info *w);

int display_minimap(t_info *w)
{
	int x;
	int y;

	y = 0;
	while (y < w->map_height)
	{
		x = 0;
		while (x < w->map_length)
		{
			generate_square(w, (DEFAULT_LENGTH * SCALE) + x * PIXEL, (DEFAULT_HEIGHT * SCALE) + y * PIXEL, get_color(w, x, y));
			x++;
		}      
		y++;
	}
	show_player(w);
	return (0);
}

int	generate_square(t_info *w, int x, int y, int color)
{
	int i = 0;
	int j = 0; 
	
	while (j < PIXEL)
	{
		i = 0;
		while (i < PIXEL)
		{
			pixel_fill(&w->img_buffer, x + i, y + j, color);
			i++;
		}
		j++;
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

void show_player(t_info *w)
{
	int x = (int)w->x_pl;
	int y = (int)w->y_pl;

	generate_square(w, (DEFAULT_LENGTH * SCALE) + x * PIXEL, (DEFAULT_HEIGHT * SCALE) + y * PIXEL, 0xFFFFFFF);

}