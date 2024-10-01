#include "cub3D.h"

static void		transfer_parsing_data(t_info *w, t_parse_data *data);
static char		**get_map(const char *map_path_name);
static void		map_parser(t_info *w, t_parse_data *data);
static void		parser_init(t_info *w, t_parse_data *data, int argc, char const *argv[]);
int				count_lines(int cub_fd);


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
	w->p_inputs.rotate_cam = 0; //temporary
	w->player_speed = PLAYER_SPEED;//temp
	w->x_strip = 0; //experimental
	w->y_strip = 0;
	w->x_strip2 = 0; //experimental
	w->y_strip2 = 0;
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
		exit (1); //TODO I think its ok but double check at the end
	}
	int line_count = count_lines(map_fd);
	if (line_count == -1)
	{
		ft_printf2(MALLOC_FAILED_MSG);
        exit (EXIT_FAILURE);
	}
	if (close (map_fd) == -1)
	{
		perror("Error\nFailed to close map file");
		exit (1); //TODO I think its ok but double check at the end
	}
	map_fd = open(map_path_name, O_RDONLY);
	if (map_fd == -1)
	{
		perror("Error\nFailed to open map file");
		exit (1); //TODO I think its ok but double check at the end
	}
    map = get_map_file2d(map_fd, line_count);
    print_map(map); //TODELETE
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
	if (data->map_start == INVALID_MAP)
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
	printf("map start value is %i\n", data->map_start);
	w->actual_map = &w->map_file[data->map_start];
	w->floor_v.r = data->floor_colors.r;
	w->floor_v.g = data->floor_colors.g;
	w->floor_v.b = data->floor_colors.b;
	w->ceiling_v.r = data->ceiling_colors.r;
	w->ceiling_v.g = data->ceiling_colors.g;
	w->ceiling_v.b = data->ceiling_colors.b;
}

static void debug_print_printed_parameters(t_parse_data *data)
{
	printf("My parameters are :\n\
		- NO_texts = %s\n\
		- SO_texts = %s\n\
		- WE_texts = %s\n\
		- EA_texts = %s\n\
		- DO_texts = %s\n\
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
		, data->DO_texts
		, data->floor_colors.r
		, data->floor_colors.g
		, data->floor_colors.b
		, data->ceiling_colors.r
		, data->ceiling_colors.g
		, data->ceiling_colors.b);	
}

int	count_lines(int cub_fd)
{
	char	*line;
	int		gnl_status;
	int		line_count;

	gnl_status = 0;
	line_count = 0;
	line = get_next_line_safe(cub_fd, &gnl_status);
	while (line)
	{
		line_count++;
		free(line);
		line = get_next_line_safe(cub_fd, &gnl_status);
	}
	// free(line); is this necessary
	if (gnl_status == 1)
		return (-1);
	return (line_count);
}
