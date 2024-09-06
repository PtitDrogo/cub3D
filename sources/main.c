# include "../includes/parsing.h"

static void debug_print_printed_parameters(t_parse_data *data);

int main(int argc, char const *argv[])
{
	t_info 			w;
	t_parse_data	data;
	int				cub_fd;

	if (argc != 2)
	{
		ft_printf2("Invalid number of arguments\n");
		return (1);
	}
	ft_memset(&w, 0, sizeof(w));
	ft_bzero(&data, sizeof(data)); //set struct to NULL
	//First hint of parsing test
	cub_fd = open(argv[1], O_RDONLY);
	if (cub_fd == -1)
	{
		perror("Error opening map file\n"); //we can actually use perror here since open is a system call !
		return (1);
	}
	w.map_file = get_map_file(cub_fd);
	// print_map(w.map_file);
	if (w.map_file == NULL)
		return (1);
	//Parsing file, fills the data in data
	int map_start = big_parser(w.map_file, &data);
	debug_print_printed_parameters(&data);
	if (map_start == -1) //this means error
	{	
		printf("There was an error of type %i! Exiting ...\n", data.status);
		ft_free_array((void *)w.map_file);
		return (1); //PRINT ERROR MESSAGE HERE
	}	
	else
	{
		w.actual_map = &w.map_file[map_start]; //this never needs to be freed
		//Feed the above to map parser;
	}
	close(cub_fd);

	//FUNCTION TO FILL W STRUCT WITH DATA FROM PARSE STRUCT
	if (!is_map_valid(&w, w.actual_map))
	{
		ft_free_array((void *)w.map_file);
		exit(0);
	}
	
	find_player(&w);
	if (!load_window(&w))
		return (1);
	// draw_all(&w);
	mlx_hook(w.id_wind, KeyPress, KeyPressMask, deal_key, &w);
	mlx_hook(w.id_wind, DestroyNotify, StructureNotifyMask, free_window, &w);
	mlx_loop_hook(w.id_mlx, no_events, &w);
	mlx_loop(w.id_mlx);
    return (0);
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
