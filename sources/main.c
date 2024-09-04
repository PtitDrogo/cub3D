# include "parsing.h"

int main(int argc, char const *argv[])
{
	//DO Parsing
    //do the Cube


	// t_info 	w;  //temporaire
	t_parse_data data;
    char 	**map_file;
	int 	cub_fd;

	if (argc != 2)
	{
		ft_printf2("Invalid number of arguments\n");
		return (0);
	}
	//First hint of parsing test
	
	cub_fd = open(argv[1], O_RDONLY);
	if (cub_fd == -1)
	{
		perror("Error opening map file\n"); //we can actually use perror here since open is a system call !
		return (1);
	}

	map_file = get_map_file(cub_fd);
	if (map_file == NULL)
		return (1); 
	for(int i = 0; map_file[i]; i++)
	{
		ft_printf("%s\n", map_file[i]);
	}

	ft_bzero(&data, sizeof(data));
	//Parsing file, fills the data in data
	if (big_parser(map_file, &data) == 1) //we can have fun with error codes here idk;
		return (1);
	//test if it worked
	// if (!load_window(&w))
	// 	return (1);
	// draw_all(&w);
	// mlx_hook(w.id_wind, KeyPress, KeyPressMask, deal_key, &w);
	// mlx_hook(w.id_wind, DestroyNotify, StructureNotifyMask, free_window, &w);
	// mlx_loop_hook(w.id_mlx, no_events, &w);
	// mlx_loop(w.id_mlx);

	//tmp cleanup;
	ft_free_array((void *)map_file);
	close(cub_fd);
    return 0;
}
