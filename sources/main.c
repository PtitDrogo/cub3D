# include "cub3D.h"

int main(int argc, char const *argv[])
{
	t_info 			w;
	t_parse_data	data;

	init_game(&w, &data, argc, argv);
	set_rays(&w);
	if (!load_window(&w))
		return (1);
	load_sprites(&w);
	// draw_all(&w);
	mlx_hook(w.id_wind, KeyPress, KeyPressMask, deal_key, &w);
	mlx_hook(w.id_wind, DestroyNotify, StructureNotifyMask, free_window, &w);
	mlx_loop_hook(w.id_mlx, no_events, &w);
	mlx_loop(w.id_mlx);
    return (0);
}
