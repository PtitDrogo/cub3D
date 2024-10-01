// #include "cub3D.h"

// static void play_frames(t_info *w, t_image *pic);

// void play_animation(t_info *w)
// {
// 	if (w->anim_playing == false)
// 		return ;
// 	if (w->anim_frames >= 20 && w->anim_frames <= 30)
//         play_frames(w, &w->gun1);
// 	else if (w->anim_frames >= 10 && w->anim_frames <= 20)
//         play_frames(w, &w->gun2);
// 	else if (w->anim_frames >= 0 && w->anim_frames <= 10)
//         play_frames(w, &w->gun1);
// 	w->anim_frames--;
// 	if (w->anim_frames == 0)
// 		w->anim_playing = false;
// }

// static void play_frames(t_info *w, t_image *pic)
// {
//     int x;
//     int y;
//     int bits_per_pixel = pic->bits_per_pixel / 8;
//     int off_set_x;
//     int off_set_y;

//     off_set_x = DEFAULT_LENGTH / 2.5;
//     off_set_y = DEFAULT_HEIGHT / 2.5;

//     y = 0;
//     while (y < pic->height)
//     {
//         x = 0;
//         while (x < pic->width)
//         {
//             char * color;
//             color = pic->pix_addr + (y * pic->size_line) + (x * (bits_per_pixel));
//             if (*(unsigned int *)color != 0xFF000000)	
//                 pixel_fill(&w->img_buffer, x + off_set_x, y + off_set_y, *(unsigned int *)color);
//             //DEFAULT_LENGTH / 3 is a random value that can be changed.
//             //Reality is i dont get why animation doesnt play in the top left initially.
//             x++;
//         }      
//         y++;
//     }
// }

