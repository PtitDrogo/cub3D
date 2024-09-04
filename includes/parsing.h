#ifndef Parsing_H
# define Parsing_H

# include <../libft/includes/libft.h>
# include "../minilibx-linux/mlx_int.h"
# include "../minilibx-linux/mlx.h"
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>

# define MAX_HEIGHT 2100 // bruteforce, recuperable ailleurs
# define MAX_LENGHT 3905 // taille max pour ecran mac

typedef struct s_parse 
{
    int hi;
} t_parse;

typedef struct s_parse_data
{
    size_t  map_heigth;
    size_t  map_width;
    char *  map_textures; //There will be a lot of these
    
    // - Map heigth map width;
    // - Les textures;
    // - Les couleurs;
} t_parse_data;

typedef struct t_w_info
{
	void	*id_mlx;
	void	*id_wind;
	size_t	w_height;
	size_t	w_lenght;
}				t_info;

//---------------------Functions---------------------//
char **get_map_file(int cub_fd);
int	no_events(t_info *w);
int	deal_key(int id_key, t_info *w);
int	free_window(t_info *w);
int	load_window(t_info *w);

#endif
