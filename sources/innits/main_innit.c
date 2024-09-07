#include "cub3D.h"

static void		transfer_parsing_data(t_info *w, t_parse_data *data);
static char 	**get_map(const char *map_path_name);
static void		map_parser(t_info *w, t_parse_data *data);
static void    	parser_init(t_info *w, t_parse_data *data, int argc, char const *argv[]);

//TO delete
static void debug_print_printed_parameters(t_parse_data *data);

void	init_game(t_info *w, t_parse_data *data, int argc, char const *argv[])
{
	parser_init(w, data, argc, argv);
	values_parser(w->map_file, data);
	debug_print_printed_parameters(data); //DEBUG
	map_parser(w, data);
	return ;
}

static void    parser_init(t_info *w, t_parse_data *data, int argc, char const *argv[])
{
	if (argc != 2)
	{
		ft_printf2("Error\nInvalid number of arguments\n");
		exit (EXIT_FAILURE);
	}
	ft_bzero(w, sizeof(*w));
	ft_bzero(data, sizeof(*data));
	w->map_file = get_map(argv[1]);
}

static char **get_map(const char *map_path_name)
{
    int map_fd;
    char **map;

    map_fd = open(map_path_name, O_RDONLY);
	if (map_fd == -1)
	{
		perror("Error\nFailed to open map file");
		exit (1);
	}
    map = get_map_file2D(map_fd);
    print_map(map); //DEBUG TO DELETE
	if (map == NULL)
	{	
        ft_printf2(MALLOC_FAILED_MSG);
        exit (EXIT_FAILURE);
    }
	close(map_fd);
	return (map);
}

static void	map_parser(t_info *w, t_parse_data *data)
{
	if (data->map_start == INVALID_MAP) //this means error
	{	
		print_error_msg(data->status);
		ft_free_array((void *)w->map_file);
		exit (EXIT_FAILURE);
	}
	transfer_parsing_data(w, data);
	if (!is_map_valid(w, w->actual_map))
	{
		ft_free_array((void *)w->map_file);
		exit(0);
	}
	find_player(w);
	return ;
}
static void	transfer_parsing_data(t_info *w, t_parse_data *data)
{
	w->actual_map = &w->map_file[data->map_start];
	w->floor_v.r = data->floor_colors.r;
	w->floor_v.g = data->floor_colors.g;
	w->floor_v.b = data->floor_colors.b;
	w->ceiling_v.r = data->ceiling_colors.r;
	w->ceiling_v.g = data->ceiling_colors.g;
	w->ceiling_v.b = data->ceiling_colors.b;
}


// static void	init_images(t_info *w, t_parse_data *data)
// {
// 	int		*width;
// 	int		*height;
// 	void	*mlx;

// 	mlx = w->id_mlx;
// 	width = &(w->img_width);
// 	height = &(w->img_height);
// 	w->wall = mlx_xpm_file_to_image(mlx, "./img/wall.xpm", width, height);
// 	w->coin = mlx_xpm_file_to_image(mlx, "./img/coin.xpm", width, height);
// 	w->floor = mlx_xpm_file_to_image(mlx, "./img/floor.xpm", width, height);
// 	w->hero = mlx_xpm_file_to_image(mlx, "./img/hero.xpm", width, height);
// 	w->exit = mlx_xpm_file_to_image(mlx, "./img/end.xpm", width, height);
// 	// if (game_img_check(w) == 0)
// 	// {
// 	// 	perror("Error\nfailed to load img");
// 	// 	exit_w(w);
// 	// }
// }

//TO delete eventually
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
