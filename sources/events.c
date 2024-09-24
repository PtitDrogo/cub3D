#include "cub3D.h"

static void		dda_innit(t_info *w, int i);
static void		apply_texture(t_info *w);
static t_image	*get_texture(t_info *w);
static void		draw_line(t_info *w, int x);
static int		pixel_color(t_info *data, int texture_y);

/*
	x = 0;
	while (x < SCREENWIDTH)
	{
		pre_dda(data->cast, player, x);
		dda(data->cast, data);
		apply_texture(data);
		draw_line(data->cast, data, x);
		x++;
	}
*/
// void	reprint_screen(t_info *w)
// {
// 	int	i;

// 	i = 0;
// 	draw_floor_sky(DEFAULT_LENGTH, DEFAULT_HEIGHT, w);
// 	while (i < DEFAULT_LENGTH)
// 	{
// 		dda_innit(w, i);
// 		movetoFirstXY(w, w->rayDirX, w->rayDirY);
// 		w->distWall = applyDDA(w, 0);
// 		apply_texture(w);
// 		getDrawLimits(w);
// 		draw_line(w, i);
// 		i++;
// 	}
// 	mlx_put_image_to_window(w->id_mlx, w->id_wind, w->img_buffer.img_ptr, 0, 0);
// }

// void	adjust_player_pos(t_info *w)
// {
// 	int	plain_x;
// 	int	plaix_y;

// 	if (w->x_pl > (int)w->x_pl + 0.9)
// 		plain_x = (int)w->x_pl + 1;
// 	if (w->x_pl <= (int)w->x_pl + 0.9)
// 		plain_x = (int)w->x_pl;
// 	if (w->y_pl > (int)w->y_pl + 0.9)
// 		plain_x = (int)w->y_pl + 1;
// 	if (w->y_pl <= (int)w->y_pl + 0.9)
// 		plain_x = (int)w->y_pl;
// 	if (w->actual_map[plain_y][plain_x] == '1')
// 	{
// 		if ((plain_x - (w->x_pl - 1)) < 0.5) // trop pres
// 		{
// 			w->x_pl -= 0.3;
// 		}
// 	}
// }

int	no_events(t_info *w)
{
	int	i;

	i = 0;
	// adjust_player_pos(w);
	move_player(w);
	draw_floor_sky(DEFAULT_LENGTH, DEFAULT_HEIGHT, w);
	while (i < DEFAULT_LENGTH)
	{
		dda_innit(w, i);
		movetoFirstXY(w, w->rayDirX, w->rayDirY);
		w->distWall = applyDDA(w, 0);
		apply_texture(w);
		getDrawLimits(w);
		draw_line(w, i);
		i++;
	}
	mlx_put_image_to_window(w->id_mlx, w->id_wind, w->img_buffer.img_ptr, 0, 0);
	return (0);
}

// int	apply_fog(int color)
// {
// 	int	red;
// 	int	blue;
// 	int	green;
// 	red = (color & 0xFF000000) >> 24;
// 	green = (color & 0x00FF0000) >> 16;
// 	blue = (color & 0x0000FF00) >> 8;
	
// 	red = red - (red * 20 /100);
// 	blue = blue - (blue * 20 /100);
// 	green = green - (green * 20 /100);

// 	color = rgb_squeeze(red, green, blue);
// 	return (color);
// }

static void	draw_line(t_info *w, int x)
{
	int	y;
	int	scaling;
	int	color;
	int	texture_y;

	y = w->draw_start;
	//We are going through every pixel of the vertical line and putting it in our buffer img;
	while (y <= w->draw_end)
	{
		scaling = (y * 256) - DEFAULT_HEIGHT * 128 + w->line_height * 128; //Tres utile !
		// scaling = 1;
		texture_y = ((scaling * w->n_wall.height) / w->line_height) / 256;
		if (texture_y < 0)
			texture_y = 0; //Pour les segfaults dans les coins
		if (texture_y >= w->n_wall.height) //IMAGE TROP GROSSE LOL OU TROP PETITE QUI SAIT
			texture_y = w->n_wall.height - 1;
		color = pixel_color(w, texture_y);
		// color = apply_fog(color);
		pixel_fill(&w->img_buffer, x, y, color);
		y++;
	}
}

static int	pixel_color(t_info *w, int texture_y)
{
	char			*color;
	t_image			*texture;

	texture = w->in_use_texture;
	color = texture->pix_addr + (texture_y * texture->size_line) + (w->texture_x * (texture->bits_per_pixel / 8));
	return (*(unsigned int *)color); //casting very important
}

static void	apply_texture(t_info *w)
{
	double	touched_wall;

	w->in_use_texture = get_texture(w);
	if (w->side == 0)
		touched_wall = (w->distWall * w->rayDirY) + w->y_pl;
	else
		touched_wall = (w->distWall * w->rayDirX) + w->x_pl;
	touched_wall -= floor(touched_wall);
	w->texture_x = (int)(touched_wall * (double)w->n_wall.width); //It could be any texture i just want the standard width
	// printf("texture x is = %i\n", w->texture_x);
	if ((w->side == 0 && w->rayDirX > 0) || (w->side == 1 && w->rayDirY < 0))
		w->texture_x = w->n_wall.width - w->texture_x - 1;
	/*
	The last condition checks if:
	The ray hit a vertical wall AND the player is facing right (positive X)
	OR
	The ray hit a horizontal wall AND the player is facing up (negative Y)
	If either of these conditions is true, the code flips the texture horizontally:
	data->texture_x = data->textures[0].width - data->texture_x - 1;
	This operation mirrors the texture coordinate. If texture_x was 10 in a 64-pixel wide texture, it becomes 53 (64 - 10 - 1).*/
}

static t_image	*get_texture(t_info *w)
{
	if (w->side == 0)
	{
		if (w->rayDirX > 0)
			return (&w->e_wall);
		else
			return (&w->w_wall);
	}
	else
	{
		if (w->rayDirY > 0)
			return (&w->s_wall);
		else
			return (&w->n_wall);
	}
}


static	void dda_innit(t_info *w, int i)
{
	w->cameraX = 2 * i / (double)DEFAULT_LENGTH - 1;
	w->rayDirX = w->vectors.xPos + w->vectors.xCam * w->cameraX;
	w->rayDirY = w->vectors.yPos + w->vectors.yCam * w->cameraX;
	w->current_map_x = (int)w->x_pl;
	w->current_map_y = (int)w->y_pl;
	if (w->rayDirX == 0)
		w->vectors.deltaX = 1e30;
	else
		w->vectors.deltaX = fabs(1 / w->rayDirX);
		// w->vectors.deltaX = sqrt(1 + (w->rayDirY * w->rayDirY) / (w->rayDirX * w->rayDirX));
	if (w->rayDirY == 0)
		w->vectors.deltaY = 1e30;
	else
		w->vectors.deltaY = fabs(1 / w->rayDirY);
		// w->vectors.deltaY = sqrt(1 + (w->rayDirX * w->rayDirX) / (w->rayDirY * w->rayDirY));
	return ;
}



void	rotate_camera(t_info *w, int coef)
{
	double	saveDirX;
	double	savePlaneX;
	double	camMultiplier;

	// camMultiplier = coef * CAM_SPEED;
	if (coef < 0)
		camMultiplier = -CAM_SPEED;
	else
		camMultiplier = CAM_SPEED; 
	saveDirX = w->vectors.xPos;
	w->vectors.xPos = w->vectors.xPos * cos(camMultiplier) - w->vectors.yPos * sin(camMultiplier);
	w->vectors.yPos = saveDirX * sin(camMultiplier) + w->vectors.yPos * cos(camMultiplier);
	savePlaneX = w->vectors.xCam;
	w->vectors.xCam = w->vectors.xCam * cos(camMultiplier) - w->vectors.yCam * sin(camMultiplier);
	w->vectors.yCam = savePlaneX * sin(camMultiplier) + w->vectors.yCam * cos(camMultiplier);
}

  void	moove_up(t_info *w)
{
	if(w->actual_map[(int)(w->y_pl)][(int)(w->x_pl + (w->vectors.xPos * w->player_speed))] == '0')
		w->x_pl += w->vectors.xPos * w->player_speed;
	if(w->actual_map[(int)(w->y_pl + (w->vectors.yPos * w->player_speed))][(int)(w->x_pl)] == '0')
		w->y_pl += w->vectors.yPos * w->player_speed;
}

  void	moove_down(t_info *w)
{
	if(w->actual_map[(int)(w->y_pl) ][(int)(w->x_pl - (w->vectors.xPos * w->player_speed))] == '0')
		w->x_pl -= w->vectors.xPos * w->player_speed;
	if(w->actual_map[(int)(w->y_pl - (w->vectors.yPos * w->player_speed))][(int)(w->x_pl)] == '0')
		w->y_pl -= w->vectors.yPos * w->player_speed;
}

void    moove_right(t_info *w)
{
	if(w->actual_map[(int)w->y_pl][(int)(w->x_pl + w->vectors.xCam * w->player_speed)] == '0')
		w->x_pl += w->vectors.xCam * w->player_speed;
	if(w->actual_map[(int)(w->y_pl + (w->vectors.yCam * w->player_speed))][(int)w->x_pl] == '0')
		w->y_pl += w->vectors.yCam * w->player_speed;
}

void	moove_left(t_info *w)
{
	if(w->actual_map[(int)w->y_pl][(int)(w->x_pl - (w->vectors.xCam * w->player_speed))] == '0')
		w->x_pl -= w->vectors.xCam * w->player_speed;
	if(w->actual_map[(int)(w->y_pl - (w->vectors.yCam * w->player_speed))][(int)w->x_pl] == '0')
		w->y_pl -= w->vectors.yCam * w->player_speed;
}

void	move_player(t_info *w)
{
	if (w->p_inputs.going_up == true)
		moove_up(w);
	if (w->p_inputs.going_down == true)
		moove_down(w);
	if (w->p_inputs.going_left == true)
		moove_left(w);
	if (w->p_inputs.going_right == true)
		moove_right(w);
	if (w->p_inputs.rotate_cam != 0)
		rotate_camera(w, w->p_inputs.rotate_cam);
	// printf("xPos is %f\n", w->vectors.xPos);
	// printf("yPos is %f\n", w->vectors.yPos);
}

int	deal_key(int id_key, t_info *w)
{
	if (id_key == XK_Escape)
		free_window(w);
	if (id_key == XK_s)
		w->p_inputs.going_down = true;
	if (id_key == XK_w)
		w->p_inputs.going_up = true;
	if (id_key == XK_d)
		w->p_inputs.going_right = true;
	if (id_key == XK_a)
		w->p_inputs.going_left = true;
	if (id_key == XK_Left)
		w->p_inputs.rotate_cam -= 1;
	if (id_key == XK_Right)
		w->p_inputs.rotate_cam += 1;
	if (id_key == XK_Shift_L)
		w->player_speed *= 2;
	return (0);
}


