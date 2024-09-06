# include "parsing.h"

static void debug_print_printed_parameters(t_parse_data *data);

int main(int argc, char const *argv[])
{
	// t_info 	w;  //temporaire
	t_parse_data data;
    char 	**map_file;
	int 	cub_fd;

	if (argc != 2)
	{
		ft_printf2("Invalid number of arguments\n");
		return (0);
	}
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
	ft_printf("\n");
	ft_bzero(&data, sizeof(data));
	
	//Parsing file, fills the data in data
	int map_start = big_parser(map_file, &data);
	debug_print_printed_parameters(&data);
	if (map_start == -1) //this means error
	{	
		printf("There was an error of type %i! Exiting ...\n", data.status);
		ft_free_array((void *)map_file);
		return (1); //PRINT ERROR MESSAGE HERE
	}	
	else
	{
		// char **actual_map = &map_file[map_start]; //this never needs to be freed
		//Feed the above to map parser;
	
	}

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


static void debug_print_printed_parameters(t_parse_data *data)
{
	printf("My parameters are :\n\
		- NO_texts = %s\n\
		- SO_texts = %s\n\
		- WE_texts = %s\n\
		- EA_texts = %s\n\
		- FLOOR_r = %i\n\
		- FLOOR_g = %i\n\
		- FLOOR_b = %i\n\
		- Ceiling_r = %i\n\
		- Ceiling_g = %i\n\
		- Ceiling_b = %i\n", 
		  data->NO_texts
		, data->SO_texts
		, data->WE_texts
		, data->EA_texts
		, data->floor_colors.r
		, data->floor_colors.g
		, data->floor_colors.b
		, data->ceiling_colors.r
		, data->ceiling_colors.g
		, data->ceiling_colors.b);
	
}
