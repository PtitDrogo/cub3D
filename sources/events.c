/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfreydie <tfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:50:30 by tfreydie          #+#    #+#             */
/*   Updated: 2024/10/07 16:26:22 by tfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void		apply_texture(t_info *w);
static t_image	*get_texture(t_info *w);
static void		draw_line(t_info *w, int x);

int	no_events(t_info *w)
{
	int	i;

	i = 0;
	move_player(w);
	draw_floor_sky(DEFAULT_LENGTH, DEFAULT_HEIGHT, w);
	while (i < DEFAULT_LENGTH)
	{
		dda_innit(w, i);
		goto_first_xy(w, w->ray_dir_x, w->ray_dir_y);
		w->distwall = apply_dda(w, 0);
		apply_texture(w);
		get_drawlimits(w);
		draw_line(w, i);
		i++;
	}
	display_minimap(w);
	play_animation(w);
	mlx_put_image_to_window(w->id_mlx, w->id_wind, w->img_buffer.img_ptr, 0, 0);
	return (0);
}

static void	draw_line(t_info *w, int x)
{
	int	y;
	int	scaling;
	int	color;
	int	textur_y;

	y = w->draw_start;
	while (y <= w->draw_end)
	{
		scaling = (y * 256) - DEFAULT_HEIGHT * 128 + w->line_height * 128;
		textur_y = (scaling * w->in_use_texture->height / w->line_height) / 256;
		if (textur_y < 0)
			textur_y = 0;
		if (textur_y >= w->in_use_texture->height)
			textur_y = w->in_use_texture->height - 1;
		color = pixel_color(w, textur_y);
		pixel_fill(&w->img_buffer, x, y, color);
		y++;
	}
}

static void	apply_texture(t_info *w)
{
	double	touched_wall;

	w->in_use_texture = get_texture(w);
	if (w->side == 0)
		touched_wall = (w->distwall * w->ray_dir_y) + w->y_pl;
	else
		touched_wall = (w->distwall * w->ray_dir_x) + w->x_pl;
	touched_wall -= floor(touched_wall);
	w->texture_x = (int)(touched_wall * (double)w->in_use_texture->width);
	if ((w->side == 0 && w->ray_dir_x < 0)
		|| (w->side == 1 && w->ray_dir_y > 0))
		w->texture_x = w->in_use_texture->width - w->texture_x - 1;
}

static t_image	*get_texture(t_info *w)
{
	if (w->is_door)
		return (&w->assets.m_door);
	if (w->side == 0)
	{
		if (w->ray_dir_x > 0)
			return (&w->assets.e_wall);
		else
			return (&w->assets.w_wall);
	}
	else
	{
		if (w->ray_dir_y > 0)
			return (&w->assets.s_wall);
		else
			return (&w->assets.n_wall);
	}
}

void	dda_innit(t_info *w, int i)
{
	w->camera_x = 2 * i / (double)DEFAULT_LENGTH - 1;
	w->ray_dir_x = w->vectors.x_pos + w->vectors.x_cam * w->camera_x;
	w->ray_dir_y = w->vectors.y_pos + w->vectors.y_cam * w->camera_x;
	w->current_map_x = (int)w->x_pl;
	w->current_map_y = (int)w->y_pl;
	if (w->ray_dir_x == 0)
		w->vectors.delta_x = 1e30;
	else
		w->vectors.delta_x = fabs(1 / w->ray_dir_x);
	if (w->ray_dir_y == 0)
		w->vectors.delta_y = 1e30;
	else
		w->vectors.delta_y = fabs(1 / w->ray_dir_y);
	return ;
}
