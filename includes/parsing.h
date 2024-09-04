#ifndef Parsing_H
# define Parsing_H

# include "../libft/includes/libft.h"
# include "mlx_int.h"
# include "mlx.h"
# include <stdlib.h>
# include <limits.h>
# include <linux/limits.h>
# include <limits.h>
# include <fcntl.h>

# define MAX_HEIGHT 2100 // bruteforce, recuperable ailleurs
# define MAX_LENGHT 3905 // taille max pour ecran mac

# define ERR_TOO_MANY_PATHS 700
# define ERR_PATH_TOO_BIG	701
# 

typedef struct s_rgb
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
} t_rgb;

typedef struct s_parse_data
{
	size_t  map_heigth;
	size_t  map_width;
	char	NO_textures[PATH_MAX];
	char	SO_textures[PATH_MAX];
	char	WE_textures[PATH_MAX];
	char	EA_textures[PATH_MAX];
	t_rgb	floor_colors;
	t_rgb	ceiling_colors;
	int		status;
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


//---------------------Parsing---------------------//
bool	is_white_space(char c);
int		big_parser(char **file, t_parse_data *data);
size_t	strlen_until_whitespace(const char *s);

#endif


0
1111111
1000001
1011101
101 101
1011101
1000001
1111111