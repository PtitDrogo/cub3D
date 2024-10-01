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
# include <math.h>

# define MAX_HEIGHT 2100 // bruteforce, recuperable ailleurs
# define MAX_LENGTH 3905 // taille max pour ecran mac
# define DEFAULT_LENGTH 1700
# define DEFAULT_HEIGHT 1200
# define SPRITE_HEIGHT 64
# define SPRITE_LENGTH 64
# define CAM_SPEED 0.030
# define PLAYER_SPEED 0.090
# define MAX_ZOOM 0.2

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
} 			t_rgb;

typedef struct s_input
{
	bool		going_up;
	bool		going_down;
	bool		going_left;
	bool		going_right;
	int			rotate_cam;
} 			t_input;

typedef struct s_parse_data
{
	char			NO_texts[PATH_MAX];
	char			SO_texts[PATH_MAX];
	char			WE_texts[PATH_MAX];
	char			EA_texts[PATH_MAX];
	char			DO_texts[PATH_MAX];
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
	void	*img_ptr;		//Contains return value of mlx_xpm_file_to_image()
	char	*pix_addr;		//Begining of the memory area where the image is stored
	int		bits_per_pixel;	//Number of bits needed to represent a pixel color
	int		size_line; 		//Number of bytes used to store one line of the image
	int		endian;			//0 = Little endian, 1 = Big endian
}				t_image;

typedef struct t_m_vector
{
	double	xPos; //x of player vector (dirX)
	double	yPos; //y of player vector (dirY)
	double	xCam; //x of cam vector (planeX)
	double	yCam; //y of cam vector (planeY)
	double	nextDistX;	//Length of ray from current position to next x-side (sideDistX)
	double	nextDistY;	//Length of ray from current position to next y-side (sideDistY)
	double	deltaX;		//Length of ray from one x to next x-side (deltaDistX)
	double	deltaY;		//Length of ray from one y to next y-side (deltaDistY)
	int		stepX;		//How much to step in x
	int		stepY;		//How much to step in y
}				t_vector;

typedef struct t_w_info
{
	void			*id_mlx; 		//MLX Session ID
	void			*id_wind;		//Window ID
	char			**map_file;		//Map[][] with NO, SE, RGB...
	char			**actual_map;	//Map[][] only
	int				side;			//side hit by ray
	int				map_height;		//Number of rows
	int				map_length;		//Size of longest line
	int				current_map_x;	//Current x on the map, int (mapX)
	int				current_map_y;	//Current y on the map, int (mapY)
	double			x_pl; 			//Player X (posX)
	double			y_pl; 			//Player Y (posY)
	double			player_speed;
	bool			is_door;
	bool			OpDoorFound ; //NEW
	int				x_strip; //NEW
	int				y_strip; //NEW
	int				x_strip2; //NEW
	int				y_strip2; //NEW
	t_input			p_inputs;
	t_image			img_buffer;     //The actual image we are changing pixel in before we call the function to show it on screen; 
	t_image			*in_use_texture; //added this to store which texture to use for a ray hit
	t_image			m_door; // ADDED DOOR 2
	t_image			n_wall;
	t_image			s_wall;
	t_image			e_wall;
	t_image			w_wall;
	t_rgb			floor_v;
	t_rgb			ceiling_v;
	t_vector		vectors;
	//animation
	t_image			gun1;
	t_image			gun2;

	//Tfreydie variables Im adding here for convenience.
	double			rayDirX;  //w->vectors.xPos + w->vectors.xCam * cameraX;
	double			rayDirY;  //w->vectors.yPos + w->vectors.yCam * cameraX;
	double			cameraX;  //2 * i / (double)DEFAULT_LENGTH - 1;
	double				distWall; // = applyDDA(w, 0);
	int					texture_x; //position of the texture I think ?
	int					line_height;
	int					draw_start;
	int					draw_end;

	bool			anim_playing;
	int				anim_frames;
	//E = bool = true.
	//int frame = 30; for example;

}				t_info;

//---------------------Functions---------------------//
char 	**get_map_file2d(int cub_fd, int line_count);
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
void	print_map(char **map);	//Only for debug, to delete after
bool	is_map_char(char c);
bool	is_direction_c(char c);
void	find_player(t_info *w); //Set player x | y
void	set_rays(t_info *w); 	//Raytracing
void	print_map_current(char **map, int x, int y);
void	get_map_height(char **map, int *height, int *length);
void	load_sprites(t_info *w, t_parse_data *d);

//---------------------Render---------------------//
void	pixel_fill(t_image *img, int x, int y, int color);
int		rgb_squeeze(int r, int g, int b);
void	draw_floor_sky(int x, int y, t_info *data);

//---------------------DDA---------------------//
double		applyDDA(t_info *w, double	wallDist, int i);
void	movetoFirstXY(t_info *w, double rayX, double rayY);
void	getDrawLimits(t_info *w);


//---------------------BONUSES---------------------//
int mouse_movement(int x, int y, t_info *w);
//tmp;
//camera
void	rotate_camera(t_info *w, int id);
//minimap
int 	display_minimap(t_info *w);
void	move_player(t_info *w);
int		generate_square(t_info *w, float x, float y, int color); //Changed this to float for the minimap but gotta double check for animation

#endif
