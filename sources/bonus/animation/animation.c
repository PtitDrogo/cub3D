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

void play_animation(t_info *w)
{
	if (w->anim_playing == false)
		return ;
	if (w->anim_frames >= 8 && w->anim_frames <= 10)
		draw_on_screen(&w->img_buffer, &w->assets.boom1);
	else if (w->anim_frames >= 6 && w->anim_frames < 8)
		draw_on_screen(&w->img_buffer, &w->assets.boom2);
	else if (w->anim_frames >= 4 && w->anim_frames < 6)
		draw_on_screen(&w->img_buffer, &w->assets.boom3);
	else if (w->anim_frames >= 2 && w->anim_frames < 4)
		draw_on_screen(&w->img_buffer, &w->assets.boom4);
	else if (w->anim_frames >= 0 && w->anim_frames < 2)
		draw_on_screen(&w->img_buffer, &w->assets.boom5);
	w->anim_frames--;
	if (w->anim_frames == 0)
		w->anim_playing = false;
}