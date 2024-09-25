# include "cub3D.h"
# include <X11/extensions/Xfixes.h>

static void		init_img_buffer(t_info *data);

int	release_countermesures(int id_key, t_info *w)
{
	if (id_key == XK_w && w->p_inputs.going_up == true)
		w->p_inputs.going_up = false;
	if (id_key == XK_s && w->p_inputs.going_down == true)
		w->p_inputs.going_down = false;
	if (id_key == XK_a && w->p_inputs.going_left == true)
		w->p_inputs.going_left = false;
	if (id_key == XK_d && w->p_inputs.going_right == true)
		w->p_inputs.going_right = false;
	if (id_key == XK_Left && w->p_inputs.rotate_cam <= 1)
		w->p_inputs.rotate_cam = 0;
	if (id_key == XK_Right && w->p_inputs.rotate_cam >= -1)
		w->p_inputs.rotate_cam = 0;
	if (id_key == XK_Shift_L)
		w->player_speed /= 2;
	return (0);
}

int main(int argc, char const *argv[])
{
	t_info 			w;
	t_parse_data	data;

	init_game(&w, &data, argc, argv);
	// set_rays(&w);
	if (!load_window(&w))
		return (1);
	load_sprites(&w, &data);
	//THEO addition (I need the mlx ptr for this so i cant put this in init game)
	init_img_buffer(&w);

	// draw_all(&w);
	// mlx_mouse_hide(w.id_mlx, w.id_wind);
	mlx_hook(w.id_wind, MotionNotify, PointerMotionMask, mouse_movement, &w);
	mlx_hook(w.id_wind, KeyPress, KeyPressMask, deal_key, &w);
	mlx_hook(w.id_wind, KeyRelease, KeyReleaseMask, release_countermesures, &w);
	mlx_hook(w.id_wind, DestroyNotify, StructureNotifyMask, free_window, &w);
	mlx_loop_hook(w.id_mlx, no_events, &w);
	mlx_loop(w.id_mlx);
    return (0);
}

static void	init_img_buffer(t_info *data)
{
	t_image *buffer;

	buffer = &data->img_buffer;
	buffer->img_ptr = mlx_new_image(data->id_mlx, DEFAULT_LENGTH, DEFAULT_HEIGHT); //Get the img buffer we will use to fill in
	if (!buffer->img_ptr)
		printf("Function (and not malloc) failed ! I will put the proper cleanup here later !\n");
	//Saw some people update a "map ready" bool here
	buffer->pix_addr = mlx_get_data_addr(buffer->img_ptr,
			&buffer->bits_per_pixel, &buffer->size_line,
			&buffer->endian); //Get start of picture and size info so we can change pixel colors (THIS DOESNT NEED TO BE FREED)
	if (!buffer->pix_addr)
		printf("The function (and not malloc) failed ! I will put the proper cleanup here later !\n");
}