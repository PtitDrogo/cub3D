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

#define  RED 0
#define  GREEN 1
#define  BLUE 2
#define  DEF_STATUS 3

# define ERR_TOO_MANY_PATHS 700
# define ERR_PATH_TOO_BIG	701
# define ERR_DEFINED_TWICE 702
# define ERR_RGB_WRONG_FORMAT 703
# define ERR_RGB_NaN 704
# define ERR_RGB_INVALID_VALUE 705
# define ERR_MAP_TOO_SOON 706
# define ERR_TOO_FEW_CHARS 707
# define ERR_INVALID_CHAR 708

typedef struct s_rgb 
{
	int 	r;
	int 	g;
	int		b;
	bool 	is_defined;
} t_rgb;


typedef struct s_parse_data
{
	size_t  		map_heigth; //Used by leo for map so maybe not here
	size_t  		map_width; //Used by leo for map so maybe not here
	char			NO_texts[PATH_MAX];
	char			SO_texts[PATH_MAX];
	char			WE_texts[PATH_MAX];
	char			EA_texts[PATH_MAX];
	t_rgb 			floor_colors;
	t_rgb 			ceiling_colors;
	int				status;
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
int		big_parser(char **file, t_parse_data *data);
bool	is_white_space(char c);
size_t	strlen_until_whitespace(const char *s);
void    update_status(int err_value, int *status);
void	rgb_parsing(const char *line, t_rgb *rgb, int *status);
bool	is_map_char(char c);
void	skip_word(const char *line, size_t *index);

#endif