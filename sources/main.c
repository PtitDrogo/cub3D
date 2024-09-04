# include "../includes/parsing.h"

int main(int argc, char const *argv[])
{
	//DO Parsing
    //do the Cube


	t_info 	w;  //temporaire
	int 	cub_fd;

	if (argc != 2)
	{
		ft_printf2("Invalid number of arguments\n");
		return (0);
	}
	ft_memset(&w, 0, sizeof(w)); //set struct to NULL
	//First hint of parsing test
	cub_fd = open(argv[1], O_RDONLY);
	if (cub_fd == -1)
	{
		perror("Error opening map file\n"); //we can actually use perror here since open is a system call !
		return (1);
	}
	w.map_file = get_map_file(cub_fd);
	if (w.map_file == NULL)
		return (1);
	close(cub_fd); 
	if (!is_map_valid(w.map_file))
	{
		ft_free_array((void *)w.map_file);
		exit(0);
	}
	if (!load_window(&w))
		return (1);
	// draw_all(&w);
	mlx_hook(w.id_wind, KeyPress, KeyPressMask, deal_key, &w);
	mlx_hook(w.id_wind, DestroyNotify, StructureNotifyMask, free_window, &w);
	mlx_loop_hook(w.id_mlx, no_events, &w);
	mlx_loop(w.id_mlx);	
    return 0;
}
