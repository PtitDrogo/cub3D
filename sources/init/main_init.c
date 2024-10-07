/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfreydie <tfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 20:07:26 by tfreydie          #+#    #+#             */
/*   Updated: 2024/10/02 20:15:38 by tfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static char		**get_map(const char *map_path_name);
static void		map_parser(t_info *w, t_parse *data);
static void		init_img_buffer(t_info *w);
static void		parse_init(t_info *w, t_parse *data,
					int argc, char const *argv[]);

void	init_game(t_info *w, t_parse *data, int argc, char const *argv[])
{
	parse_init(w, data, argc, argv);
	values_parser(w->map_file, data);
	map_parser(w, data);
	load_window(w);
	load_sprites(w, data, 0);
	init_img_buffer(w);
	return ;
}

void	parse_init(t_info *w, t_parse *data,
					int argc, char const *argv[])
{
	if (argc != 2)
		printf_exit("Error\nInvalid number of arguments\n");
	if (DEFAULT_LENGTH < MIN_LENGTH || DEFAULT_HEIGHT < MIN_HEIGHT
		|| DEFAULT_LENGTH > MAX_HEIGHT || DEFAULT_HEIGHT > MAX_HEIGHT)
	{
		printf_exit("Error\nInvalid screen size\n");
	}
	cub_check(argv[1]);
	ft_bzero(w, sizeof(*w));
	ft_bzero(data, sizeof(*data));
	w->player_speed = PLAYER_SPEED;
	w->map_file = get_map(argv[1]);
}

static char	**get_map(const char *map_path_name)
{
	int		map_fd;
	char	**map;
	int		line_count;

	map_fd = open(map_path_name, O_RDONLY);
	if (map_fd == -1)
		perror_exit("Error\nFailed to open map file");
	line_count = count_lines(map_fd);
	if (close (map_fd) == -1)
		perror_exit("Error\nFailed to close map file");
	if (line_count == -1)
		printf_exit(MALLOC_FAILED_MSG);
	map_fd = open(map_path_name, O_RDONLY);
	if (map_fd == -1)
		perror_exit("Error\nFailed to open map file");
	map = get_map_file2d(map_fd, line_count);
	if (map == NULL)
		printf_exit(MALLOC_FAILED_MSG);
	if (close(map_fd) == -1)
	{
		ft_free_array((void *)map);
		perror_exit("Error\nFailed to close map file");
	}
	return (map);
}

static void	map_parser(t_info *w, t_parse *data)
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

static void	init_img_buffer(t_info *w)
{
	t_image	*buffer;

	buffer = &w->img_buffer;
	buffer->img_ptr = mlx_new_image(w->id_mlx, DEFAULT_LENGTH, DEFAULT_HEIGHT);
	if (!buffer->img_ptr)
	{
		ft_printf2("Error\nCouldn't load mlx_image buffer\n");
		free_window(w);
	}
	buffer->pix_addr = mlx_get_data_addr(buffer->img_ptr,
			&buffer->bits_per_pixel, &buffer->size_line,
			&buffer->endian);
	if (!buffer->pix_addr)
	{
		ft_printf2("Error\nCouldn't load mlx_image buffer address\n");
		free_window(w);
	}
}
