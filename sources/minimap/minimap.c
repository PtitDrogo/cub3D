#include "cub3D.h"

int		get_color(t_info *w, int x, int y);
int		generate_square(t_info *w, float x, float y, int color);
void	show_player(t_info *w, float pixel_x, float pixel_y);

int display_minimap(t_info *w)
{
	int x;
	int y;
	float pixel_x = DEFAULT_LENGTH / w->map_length * 0.20;
	float pixel_y = DEFAULT_HEIGHT / w->map_height * 0.20;

	y = 0;
	while (y < w->map_height)
	{
		x = 0;
		while (x < w->map_length)
		{
			generate_square(w, x * pixel_x, y * pixel_y, get_color(w, x, y));
			x++;
		}      
		y++;
	}
	show_player(w, pixel_x, pixel_y);
	return (0);
}

int	generate_square(t_info *w, float x, float y, int color)
{
	int i = 0;
	int j = 0;
	float pixel_x = DEFAULT_LENGTH / w->map_length * 0.20;
	float pixel_y = DEFAULT_HEIGHT / w->map_height * 0.20;
	
	while (j < pixel_y)
	{
		i = 0;
		while (i < pixel_x)
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
	char c;

	c = w->actual_map[y][x];
	if (c == '0')
		return (0x694F8E);
	else if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (0x71);
	else if (is_white_space(c))
		return (0x002900);
	else if (c == 'D')
		return (0x582900);
	else if (c == 'O')
		return (0xd16100);
	else
		return (0xE3A5C7); //modify these colors later
}

void show_player(t_info *w, float pixel_x, float pixel_y)
{
	int x = (int)w->x_pl;
	int y = (int)w->y_pl;

	generate_square(w, x * pixel_x, y * pixel_y, 0xFFFFFFF);
}
