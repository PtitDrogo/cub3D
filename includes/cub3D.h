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

# define MAX_HEIGHT 2100
# define MAX_LENGTH 3905
# define MIN_LENGTH 1440
# define MIN_HEIGHT 810
# define DEFAULT_LENGTH 1440
# define DEFAULT_HEIGHT 810
# define SPRITE_HEIGHT 64
# define SPRITE_LENGTH 64
# define CAM_SPEED 0.030
# define PLAYER_SPEED 0.090
# define MAX_ZOOM 0.2
# define MINIMAP_MARGIN 2

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
# define ERR_NOT_XPM_FILE 711


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
	t_rgb 			floor_colors;
	t_rgb 			ceiling_colors;
	int				status;
	int				map_start;
} t_parse;

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

typedef struct s_w_assets
{
	t_image			m_door; 		
	t_image			n_wall;
	t_image			s_wall;
	t_image			e_wall;
	t_image			w_wall;
	t_image			b1;
	t_image			b2;
	t_image			b3;
	t_image			b4;
	t_image			b5;
	t_image			b6;
	t_image			b7;
	t_image			b8;
	t_image			b9;
	t_image			b10;
	t_image			c1;
	t_image			c2;
	t_image			c3;
	t_image			c4;
	t_image			c5;
	t_image			c6;
	t_image			c7;
	t_image			c8;
	t_image			c9;
	t_image			c10;
}	t_assets;

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
	int				x_strip; //NEW
	int				y_strip; //NEW
	t_image			*in_use_texture; //added this to store which texture to use for a ray hit
	t_input			p_inputs;
	t_rgb			floor_v;
	t_rgb			ceiling_v;
	t_image			img_buffer;     //The actual image we are changing pixel in before we call the function to show it on screen; 
	t_assets		assets;
	//Tfreydie variables Im adding here for convenience.
	double			rayDirX;  //w->vectors.xPos + w->vectors.xCam * cameraX;
	double			rayDirY;  //w->vectors.yPos + w->vectors.yCam * cameraX;
	double			cameraX;  //2 * i / (double)DEFAULT_LENGTH - 1;
	double				distWall; // = applyDDA(w, 0);
	int					texture_x; //position of the texture I think ?
	int					line_height;
	int					draw_start;
	int					draw_end;
	t_vector		vectors;

	bool			anim_playing;
	int				anim_frames;
	char			anim_type;

}				t_info;

//---------------------Functions---------------------//
char 	**get_map_file2d(int cub_fd, int line_count);
int		no_events(t_info *w);
int		deal_key(int id_key, t_info *w);
int		free_window(t_info *w);
int		load_window(t_info *w);


//---------------------Errors---------------------//
void	print_error_msg(int err_code);
void	perror_exit(const char *err_msg);
void	printf_exit(const char *err_msg);


//---------------------Innit---------------------//
void	init_game(t_info *w, t_parse *data, int argc, char const *argv[]);
void	transfer_parsing_data(t_info *w, t_parse *data);
int		count_lines(int cub_fd);
void	cub_check(const char *s);

//---------------------Parsing---------------------//
void	values_parser(char **file, t_parse *data);
bool	is_white_space(char c);
size_t	strlen_until_whitespace(const char *s);
void    update_status(int err_value, int *status);
void	rgb_parsing(const char *line, t_rgb *rgb, int *status);
bool	is_map_char(char c);
void	skip_word(const char *line, size_t *index);
bool	is_xpm_file(const char *s);
void	xpm_check(t_parse *data);

//---------------------Map-Parsing---------------------//
bool	is_map_valid(t_info *w, char **m_map);
void	print_map(char **map);	//Only for debug, to delete after
bool	is_map_char(char c);
bool	is_direction_c(char c);
void	find_player(t_info *w); //Set player x | y
void	print_map_current(char **map, int x, int y);
void	get_map_height(char **map, int *height, int *length);
int		load_sprites(t_info *w, t_parse *d, int err);

//---------------------Render---------------------//
void	pixel_fill(t_image *img, int x, int y, int color);
void	draw_floor_sky(int x, int y, t_info *data);

//---------------------Sprites---------------------//
int	load_bonus_boom(t_info *w);
int	load_bonus_cloud(t_info *w);
int	load_sprites(t_info *w, t_parse *d, int err);
void	load_all_address_sprites(t_info *w);;

//---------------------DDA---------------------//
void		dda_innit(t_info *w, int i);
double		applyDDA(t_info *w, double	wallDist);
void		movetoFirstXY(t_info *w, double rayX, double rayY);
void		getDrawLimits(t_info *w);
void		move_player(t_info *w);

//---------------------Keys---------------------//
int	release_countermeasure(int id_key, t_info *w);
int	deal_key(int id_key, t_info *w);


//---------------------BONUSES---------------------//
//mouse
int mouse_movement(int x, int y, t_info *w);

//camera
void	rotate_camera(t_info *w, int id);

//minimap
int 	display_minimap(t_info *w);
int		generate_square(t_info *w, float x, float y, int color);
void    remove_spaces(t_info *w);

//animation
void	draw_on_screen(t_image *img_buffer, t_image	*current_sprite);
void	play_animation(t_info *w);

//door
void	check_doors(t_info *w);

#endif
