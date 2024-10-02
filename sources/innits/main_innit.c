#include "cub3D.h"

static void		transfer_parsing_data(t_info *w, t_parse_data *data);
static char		**get_map(const char *map_path_name);
static void		map_parser(t_info *w, t_parse_data *data);
static void		parser_init(t_info *w, t_parse_data *data, int argc, char const *argv[]);
int				count_lines(int cub_fd);
static void		init_img_buffer(t_info *w);


//TO delete
// static void debug_print_printed_parameters(t_parse_data *data);

void	init_game(t_info *w, t_parse_data *data, int argc, char const *argv[])
{
	parser_init(w, data, argc, argv);
	values_parser(w->map_file, data);
	// debug_print_printed_parameters(data); //DEBUG
	map_parser(w, data);
	load_window(w);
	load_sprites(w, data, 0);
	init_img_buffer(w);
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
	w->x_strip = 0; //goatesque
	w->y_strip = 0;
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
	remove_spaces(w);
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
	if (gnl_status == 1)
		return (-1);
	return (line_count);
}

static void	init_img_buffer(t_info *w)
{
	t_image *buffer;

	buffer = &w->img_buffer;
	buffer->img_ptr = mlx_new_image(w->id_mlx, DEFAULT_LENGTH, DEFAULT_HEIGHT); //Get the img buffer we will use to fill in
	if (!buffer->img_ptr)
	{
		free_window(w);
	}
	//Saw some people update a "map ready" bool here
	buffer->pix_addr = mlx_get_data_addr(buffer->img_ptr,
			&buffer->bits_per_pixel, &buffer->size_line,
			&buffer->endian); //Get start of picture and size info so we can change pixel colors (THIS DOESNT NEED TO BE FREED)
	if (!buffer->pix_addr)
		printf("The function (and not malloc) failed ! I will put the proper cleanup here later !\n");
}