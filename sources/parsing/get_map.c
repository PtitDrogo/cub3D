#include "cub3D.h"

int	count_lines(int cub_fd);

char	**get_map_file2d(int cub_fd, int line_count)
{
	int		gnl_status;
	char	**map_file;
	int		i;

	i = 0;
	gnl_status = 0;
	map_file = ft_calloc(line_count + 1, sizeof(char *));
	if (map_file == NULL)
		return (NULL);
	while (i < line_count)
	{
		map_file[i] = get_next_line_safe(cub_fd, &gnl_status);
		if (gnl_status == 1)
			return (NULL);
		i++;
	}
	return (map_file);
}