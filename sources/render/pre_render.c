/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfreydie <tfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:12:12 by tfreydie          #+#    #+#             */
/*   Updated: 2024/10/07 16:25:55 by tfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	char	*real_color;

	real_color = img->pix_addr + (y * img->size_line)
		+ (x * (img->bits_per_pixel / 8));
	*(unsigned int *)real_color = color;
}

int	pixel_color(t_info *w, int texture_y)
{
	char			*color;
	t_image			*texture;

	texture = w->in_use_texture;
	color = texture->pix_addr + (texture_y * texture->size_line)
		+ (w->texture_x * (texture->bits_per_pixel / 8));
	return (*(unsigned int *)color);
}

static	int	rgb_squeeze(int r, int g, int b)
{
	int	color;

	color = r << 16 | g << 8 | b;
	return (color);
}
