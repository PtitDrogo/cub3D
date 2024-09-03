#include "parsing.h"

int main(int argc, char const *argv[])
{
	if (argc != 2)
	{
		ft_printf2("Invalid number of arguments\n");
		return (0);
	}
	//First hint of parsing test
	
	int cub_fd;
	cub_fd = open(argv[1], O_RDONLY);
	if (cub_fd == -1)
	{
		perror("Error opening map file\n"); //we can actually use perror here since write is a system call !
		return (1);
	}

	char **map_file;

	map_file = get_map_file(cub_fd);
	if (map_file == NULL)
		return (1); 

	//test if it worked
	for(int i = 0; map_file[i]; i++)
	{
		ft_printf("%s\n", map_file[i]);
	}

	//tmp cleanup;
	ft_free_array((void *)map_file);
	close(cub_fd);
	return 0;
}
