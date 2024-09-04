# include "parsing.h"

int main(int argc, char const *argv[])
{
	//DO Parsing
    //do the Cube


	t_info w;  //temporaire
	char *filename;
    
   if (argc != 2)
		return (ft_printf("Error\n/!\\ WRONG NB OF PARAMETERS!\n"));
	filename = argv[1];
	if (!load_window(&w))
		return (1);
	draw_all(&w);
	mlx_hook(w.id_wind, KeyPress, KeyPressMask, deal_key, &w);
	mlx_hook(w.id_wind, DestroyNotify, StructureNotifyMask, free_window, &w);
	mlx_loop_hook(w.id_mlx, no_events, &w);
	mlx_loop(w.id_mlx);
    return 0;
}
