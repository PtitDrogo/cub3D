#include "cub3D.h"

int	release_countermesures(int id_key, t_info *w)
{
	if (id_key == XK_w && w->p_inputs.going_up == true)
		w->p_inputs.going_up = false;
	else if (id_key == XK_s && w->p_inputs.going_down == true)
		w->p_inputs.going_down = false;
	else if (id_key == XK_a && w->p_inputs.going_left == true)
		w->p_inputs.going_left = false;
	else if (id_key == XK_d && w->p_inputs.going_right == true)
		w->p_inputs.going_right = false;
	else if (id_key == XK_Left && w->p_inputs.rotate_cam <= 1)
		w->p_inputs.rotate_cam = 0;
	else if (id_key == XK_Right && w->p_inputs.rotate_cam >= -1)
		w->p_inputs.rotate_cam = 0;
	else if (id_key == XK_Shift_L)
		w->player_speed /= 2;
	return (0);
}

int	deal_key(int id_key, t_info *w)
{
	if (id_key == XK_Escape)
		free_window(w);
	else if (id_key == XK_e)
		check_doors(w);
	else if (id_key == XK_s)
		w->p_inputs.going_down = true;
	else if (id_key == XK_w)
		w->p_inputs.going_up = true;
	else if (id_key == XK_d)
		w->p_inputs.going_right = true;
	else if (id_key == XK_a)
		w->p_inputs.going_left = true;
	else if (id_key == XK_Left)
		w->p_inputs.rotate_cam -= 1;
	else if (id_key == XK_Right)
		w->p_inputs.rotate_cam += 1;
	else if (id_key == XK_Shift_L)
		w->player_speed *= 2;
	return (0);
}