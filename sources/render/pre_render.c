#include "cub3D.h"

static	int	rgb_squeeze(int r, int g, int b);

void	draw_floor_sky(int x, int y, t_info *w)
{
	int			i;
	int			j;
	int			ceiling_color;
	int			floor_color;

	ceiling_color = rgb_squeeze(w->ceiling_v.r, w->ceiling_v.g, w->ceiling_v.b);
	floor_color = rgb_squeeze(w->floor_v.r, w->floor_v.g, w->floor_v.b);
	i = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			if (i > DEFAULT_HEIGHT / 2)
				pixel_fill(&w->img_buffer, j, i, floor_color);
			else
				pixel_fill(&w->img_buffer, j, i, ceiling_color);
			j++;
		}
		i++;
	}
}

void	pixel_fill(t_image *img, int x, int y, int color)
{
	char	*real_pixel_coor;

	real_pixel_coor = img->pix_addr + (y * img->size_line) + (x * (img->bits_per_pixel / 8));
	*(unsigned int *)real_pixel_coor = color;
}

static	int	rgb_squeeze(int r, int g, int b)
{
	int	color;

	color = r << 16 | g << 8 | b;
	return (color);
}