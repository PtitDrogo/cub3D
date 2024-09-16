#include "cub3D.h"

char	**get_map_file2d(int cub_fd)
{
	int		gnl_status;
	char	**map_file;
	char	*curr_line;
	char	*map;

	gnl_status = 0;
	curr_line = get_next_line_safe(cub_fd, &gnl_status);
	map = ft_calloc(1, 1);
	if (map == NULL || gnl_status == 1)
		return (free(map), NULL);
	while (curr_line)
	{
		map = ft_strjoin_free_s1(map, curr_line);
		free(curr_line);
		curr_line = get_next_line_safe(cub_fd, &gnl_status);
		if (map == NULL || gnl_status == 1)
			return (free(curr_line), NULL);
	}
	map_file = ft_split(map, '\n');
	free (map);
	return (map_file);
}
