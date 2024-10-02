#include "cub3D.h"


void	draw_on_screen(t_image *img_buffer, t_image	*current_sprite)
{
	char	*color;
	int		x_bits_pixel;
	int		x;
	int		y;

	y = 0;
	x_bits_pixel = current_sprite->bits_per_pixel / 8;
	while (y < current_sprite->height)
	{
		x = 0;
		while (x < current_sprite->width)
		{
			
			color = current_sprite->pix_addr + (y * current_sprite->size_line) + (x * x_bits_pixel);
			if (*(unsigned int *)color != 0xFF000000)	
				pixel_fill(img_buffer, x + (DEFAULT_LENGTH/2) - current_sprite->width/2,
						y + (DEFAULT_HEIGHT/2) - current_sprite->height/2, *(unsigned int *)color);
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

void play_animation(t_info *w)
{
	if (w->anim_playing == false)
		return ;
	else if (w->anim_type == 'c')
		animate_poof(w);
	else
		animate_boom(w);
}