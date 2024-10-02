# include "cub3D.h"

int main(int argc, char const *argv[])
{
	t_info 			w;
	t_parse_data	data;

	init_game(&w, &data, argc, argv);
	mlx_hook(w.id_wind, MotionNotify, PointerMotionMask, mouse_movement, &w);
	mlx_hook(w.id_wind, KeyPress, KeyPressMask, deal_key, &w);
	mlx_hook(w.id_wind, KeyRelease, KeyReleaseMask, release_countermesures, &w);
	mlx_hook(w.id_wind, DestroyNotify, StructureNotifyMask, free_window, &w);
	mlx_loop_hook(w.id_mlx, no_events, &w);
	mlx_loop(w.id_mlx);
    return (0);
}