#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/includes/libft.h"
# include "mlx_int.h"
# include "mlx.h"
# include <stdlib.h>
# include <limits.h>
# include <linux/limits.h>
# include <limits.h>
# include <fcntl.h>

# define MAX_HEIGHT 2100 // bruteforce, recuperable ailleurs
# define MAX_LENGTH 3905 // taille max pour ecran mac
# define DEFAULT_LENGTH 1000
# define DEFAULT_HEIGHT 800

# define INVALID_MAP -1

# define MALLOC_FAILED_MSG "Error\nMalloc failed\n"

# define ERR_MALLOC_FAILED 42
# define ERR_TOO_MANY_PATHS 700
# define ERR_PATH_TOO_BIG	701
# define ERR_DEFINED_TWICE 702
# define ERR_RGB_WRONG_FORMAT 703
# define ERR_RGB_NaN 704
# define ERR_MAP_TOO_SOON 705
# define ERR_TOO_FEW_CHARS 706
# define ERR_INVALID_CHAR 707
# define ERR_TOO_MANY_PLYR 708
# define ERR_ZERO_PLAYER 709
# define ERR_INVALID_CHAR_MAP 710


typedef struct s_rgb 
{
	int 	r;
	int 	g;
	int		b;
	bool 	is_defined;
} t_rgb;


typedef struct s_parse_data
{
	char			NO_texts[PATH_MAX];
	char			SO_texts[PATH_MAX];
	char			WE_texts[PATH_MAX];
	char			EA_texts[PATH_MAX];
	t_rgb 			floor_colors;
	t_rgb 			ceiling_colors;
	int				status;
	int				map_start;
} t_parse_data;

typedef struct t_my_image
{
	int		width;
	int		height;
	int		x;
	int		y;
	void	*img_ptr; //link to pointer , to free
}				t_image;

typedef struct t_m_vector
{
	double x_pl;
	double y_pl;
	double xPos;
	double yPos;
	double xCam;
	double yCam;
}				t_vector;

typedef struct t_w_info
{
	void			*id_mlx;  // mlx session id
	void			*id_wind; //window id
	char			**map_file; // split map
	char			**actual_map;
	int				map_heigth;
	int				map_lenght;
	t_image			m_door; //sprites : 
	t_image			n_wall;
	t_image			s_wall;
	t_image			e_wall;
	t_image			w_wall;
	t_rgb			floor_v;
	t_rgb			ceiling_v;
	t_vector		player;
}				t_info;

//---------------------Functions---------------------//
char 	**get_map_file2D(int cub_fd);
int		no_events(t_info *w);
int		deal_key(int id_key, t_info *w);
int		free_window(t_info *w);
int		load_window(t_info *w);
void	print_error_msg(int err_code);

//---------------------Innit---------------------//
void	init_game(t_info *w, t_parse_data *data, int argc, char const *argv[]);

//---------------------Parsing---------------------//
void	values_parser(char **file, t_parse_data *data);
bool	is_white_space(char c);
size_t	strlen_until_whitespace(const char *s);
void    update_status(int err_value, int *status);
void	rgb_parsing(const char *line, t_rgb *rgb, int *status);
bool	is_map_char(char c);
void	skip_word(const char *line, size_t *index);

//---------------------Map-Parsing---------------------//
bool	is_map_valid(t_info *w, char **m_map);
void	print_map(char **map); //only for debug, to delete after
bool	is_map_char(char c);
bool	is_direction_c(char c);
void	find_player(t_info *w); // set player x | y

#endif