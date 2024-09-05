# include "../includes/parsing.h"

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
			if (is_direction_c(w->map_file[y][x]))
			{
				w->player.x = x;
				w->player.y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}
