#ifndef Parsing_H
# define Parsing_H

# include <../libft/includes/libft.h>
# include "../minilibx-linux/mlx_int.h"
# include "../minilibx-linux/mlx.h"
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include <math.h>

# define MAX_HEIGHT 2100 // bruteforce, recuperable ailleurs
# define MAX_LENGTH 3905 // taille max pour ecran mac
// # define DEFAULT_LENGTH 1000
// # define DEFAULT_HEIGHT 800
# define DEFAULT_LENGTH 10
# define DEFAULT_HEIGHT 20

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
	double	x_pl; //Player X
	double	y_pl; //Player Y
	double	xPos; //x of player vector
	double	yPos; //y of player vector
	double	xCam; //x of cam vector
	double	yCam; //y of cam vector
	double	nextDistX; //length of ray from current position to next x-side
	double	nextDistY; //length of ray from current position to next y-side 
	double	deltaX; //length of ray from one x to next x-side
	double	deltaY; //length of ray from one y to next y-side
	int		current_map_x; // current x on the map (int)
	int		current_map_y; // current y on the map (int)
	int		stepX;	// how much to step in x
	int		stepY;	// how much to step in y
}				t_vector;

typedef struct t_w_info
{
	void			*id_mlx;  // MLX Session ID
	void			*id_wind; // Window ID
	char			**map_file; // Map in map[][] format
	int				map_heigth;
	int				map_lenght;
	t_image			m_door;
	t_image			n_wall;
	t_image			s_wall;
	t_image			e_wall;
	t_image			w_wall;
	t_rgb			floor_v;
	t_rgb			celling_v;
	t_vector		vectors;
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
void	set_rays(t_info *w); // raytracing

#endif
