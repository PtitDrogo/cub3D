#include "../../includes/parsing.h"

//get map file, maybe add a bool for if theres an error idk
char **get_map_file(int cub_fd)
{    
    //Lets store everything in a 1d array at first;
	int gnl_status = 0;
	char *curr_line;
	char *map;

	curr_line = get_next_line_safe(cub_fd, &gnl_status);
	map = ft_calloc(1, 1); // so that I dont have to be like map[0] = '\0' right after.
	if (map == NULL || gnl_status == 1)
		return (free(map), NULL);
	while (curr_line)
	{
		map = ft_strjoin_free_s1(map, curr_line);
		free(curr_line);
		curr_line = get_next_line_safe(cub_fd, &gnl_status);
		if (map == NULL || gnl_status == 1)
			return (free(curr_line), NULL); //malloc error msg later
	}
    char **map_file = ft_split(map, '\n');
    free(map);
	return(map_file);
}
