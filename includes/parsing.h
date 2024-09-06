#ifndef Parsing_H
# define Parsing_H

# include <../libft/includes/libft.h>
# include "../minilibx-linux/mlx_int.h"
# include "../minilibx-linux/mlx.h"
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>

# define MAX_HEIGHT 2100 // bruteforce, recuperable ailleurs
# define MAX_LENGTH 3905 // taille max pour ecran mac
# define DEFAULT_LENGTH 1000
# define DEFAULT_HEIGHT 800

# define TOO_MANY_PLYR_ERR 1
# define ZERO_PLAYER_ERR 2
# define INVALID_CHAR_ERR 3

typedef struct s_parse 
{
	int hi;
} t_parse;

typedef struct s_parse_data
{
	size_t	map_heigth;
	size_t	map_width;
	char *	map_textures; //There will be a lot of these
		
	// - Map heigth map width;
	// - Les textures;
	// - Les couleurs;
} t_parse_data;

typedef struct t_my_image
{
	int		width;
	int		height;
	int		x;
	int		y;
	void	*img_ptr; //link to pointer , to free
}				t_image;

typedef struct t_m_rgb
{
	unsigned char	r_value; //RGB values :
	unsigned char	g_value;
	unsigned char	b_value;
}				t_rgb;

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
	int				map_heigth;
	int				map_lenght;
	t_image			m_door; //sprites : 
	t_image			n_wall;
	t_image			s_wall;
	t_image			e_wall;
	t_image			w_wall;
	t_rgb			floor_v;
	t_rgb			celling_v;
	t_vector		player;
}				t_info;

//---------------------Functions---------------------//
char	**get_map_file(int cub_fd);
int		no_events(t_info *w);
int		deal_key(int id_key, t_info *w);
int		free_window(t_info *w);
int		load_window(t_info *w);
bool	is_map_valid(t_info *w, char **m_map);
void	print_map(char **map); //only for debug, to delete after
bool	is_allowed_char(char c);
bool	is_direction_c(char c);
bool	is_whitespace_c(char c);
void	find_player(t_info *w); // set player x | y
#endif
