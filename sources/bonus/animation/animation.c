/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfreydie <tfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:33:28 by tfreydie          #+#    #+#             */
/*   Updated: 2024/10/02 19:38:41 by tfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_on_screen(t_image *buffer, t_image	*sprite)
{
	char	*color;
	int		x_bits_pixel;
	int		x;
	int		y;

	y = 0;
	x_bits_pixel = sprite->bits_per_pixel / 8;
	while (y < sprite->height)
	{
		x = 0;
		while (x < sprite->width)
		{
			color = sprite->pix_addr + (y * sprite->size_line)
				+ (x * x_bits_pixel);
			if (*(unsigned int *)color != 0xFF000000)
				pixel_fill(buffer, x + (DEFAULT_LENGTH / 2) - sprite->width / 2,
					y + (DEFAULT_HEIGHT / 2) - sprite->height / 2,
					*(unsigned int *)color);
			x++;
		}
		y++;
	}
	return ;
}

void	animate_poof(t_info *w)
{
	if (w->anim_frames >= 10 && w->anim_frames <= 11)
		draw_on_screen(&w->img_buffer, &w->assets.cloud1);
	else if (w->anim_frames >= 9 && w->anim_frames < 10)
		draw_on_screen(&w->img_buffer, &w->assets.cloud2);
	else if (w->anim_frames >= 8 && w->anim_frames < 9)
		draw_on_screen(&w->img_buffer, &w->assets.cloud3);
	else if (w->anim_frames >= 7 && w->anim_frames < 8)
		draw_on_screen(&w->img_buffer, &w->assets.cloud4);
	else if (w->anim_frames >= 6 && w->anim_frames < 7)
		draw_on_screen(&w->img_buffer, &w->assets.cloud5);
	else if (w->anim_frames >= 5 && w->anim_frames < 6)
		draw_on_screen(&w->img_buffer, &w->assets.cloud6);
	else if (w->anim_frames >= 4 && w->anim_frames < 5)
		draw_on_screen(&w->img_buffer, &w->assets.cloud6);
	else if (w->anim_frames >= 3 && w->anim_frames < 4)
		draw_on_screen(&w->img_buffer, &w->assets.cloud7);
	else if (w->anim_frames >= 2 && w->anim_frames < 3)
		draw_on_screen(&w->img_buffer, &w->assets.cloud8);
	else if (w->anim_frames >= 1 && w->anim_frames < 2)
		draw_on_screen(&w->img_buffer, &w->assets.cloud9);
	else if (w->anim_frames >= 0 && w->anim_frames < 1)
		draw_on_screen(&w->img_buffer, &w->assets.cloud10);
	w->anim_frames--;
	if (w->anim_frames == 0)
		w->anim_playing = false;
}

void	animate_boom(t_info *w)
{
	if (w->anim_frames >= 10 && w->anim_frames <= 11)
		draw_on_screen(&w->img_buffer, &w->assets.boom1);
	else if (w->anim_frames >= 9 && w->anim_frames < 10)
		draw_on_screen(&w->img_buffer, &w->assets.boom2);
	else if (w->anim_frames >= 8 && w->anim_frames < 9)
		draw_on_screen(&w->img_buffer, &w->assets.boom3);
	else if (w->anim_frames >= 7 && w->anim_frames < 8)
		draw_on_screen(&w->img_buffer, &w->assets.boom4);
	else if (w->anim_frames >= 6 && w->anim_frames < 7)
		draw_on_screen(&w->img_buffer, &w->assets.boom5);
	else if (w->anim_frames >= 5 && w->anim_frames < 6)
		draw_on_screen(&w->img_buffer, &w->assets.boom6);
	else if (w->anim_frames >= 4 && w->anim_frames < 5)
		draw_on_screen(&w->img_buffer, &w->assets.boom6);
	else if (w->anim_frames >= 3 && w->anim_frames < 4)
		draw_on_screen(&w->img_buffer, &w->assets.boom7);
	else if (w->anim_frames >= 2 && w->anim_frames < 3)
		draw_on_screen(&w->img_buffer, &w->assets.boom8);
	else if (w->anim_frames >= 1 && w->anim_frames < 2)
		draw_on_screen(&w->img_buffer, &w->assets.boom9);
	else if (w->anim_frames >= 0 && w->anim_frames < 1)
		draw_on_screen(&w->img_buffer, &w->assets.boom10);
	w->anim_frames--;
	if (w->anim_frames == 0)
		w->anim_playing = false;
}

void	play_animation(t_info *w)
{
	if (w->anim_playing == false)
		return ;
	else if (w->anim_type == 'c')
		animate_poof(w);
	else
		animate_boom(w);
}
