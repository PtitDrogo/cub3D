#include "cub3D.h"

static void		dda_innit(t_info *w, int i);
static void		apply_texture(t_info *w);
static t_image	*get_texture(t_info *w);
static void		draw_line(t_info *w, int x);
static int		pixel_color(t_info *data, int texture_y);

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


int	no_events(t_info *w)
{
	int	i;

	i = 0;
	move_player(w);
	draw_floor_sky(DEFAULT_LENGTH, DEFAULT_HEIGHT, w);
	while (i < DEFAULT_LENGTH)
	{
		dda_innit(w, i);
		movetoFirstXY(w, w->rayDirX, w->rayDirY);
		w->distWall = applyDDA(w, 0, i);
		apply_texture(w);
		getDrawLimits(w);
		draw_line(w, i);
		i++;
	}
	mlx_put_image_to_window(w->id_mlx, w->id_wind, w->img_buffer.img_ptr, 0, 0);
	return (0);
}

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
	if (w->is_door)
		return (&w->m_door);
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
	if (w->rayDirY == 0)
		w->vectors.deltaY = 1e30;
	else
		w->vectors.deltaY = fabs(1 / w->rayDirY);
	return ;
}

void	check_doors(t_info *w)
{
	int	abs1;
	int	abs2;
	// printf("xPos id %f, yPos is %f\n", w->vectors.xPos, w->vectors.yPos);
	// printf("central ray on x:%d y:%d = %c\n", w->x_strip, w->y_strip,
	// w->actual_map[w->y_strip][w->x_strip]);
	// printf("central ray2 on x:%d y:%d = %c\n", w->x_strip2, w->y_strip2,
	// w->actual_map[w->y_strip2][w->x_strip2]);
	// printf("xPlayer is %f, yPlayer is %f\n", w->x_pl, w->y_pl);
	if (w->actual_map[w->y_strip2][w->x_strip2] == 'O')
	{
		// printf("\nabs(y_strip2 - y_pl) = %d\n", abs(w->y_strip2 - (int)w->y_pl));
		// printf("\nabs(x_strip2 - x_pl) = %d\n", abs(w->x_strip2 - (int)w->x_pl));
		abs1 = abs(w->y_strip2 - (int)w->y_pl);
		abs2 = abs(w->x_strip2 - (int)w->x_pl);
		if (( abs1 <= 1) && (abs2 <= 1) && (abs1 + abs2 > 0))
			w->actual_map[w->y_strip2][w->x_strip2] = 'D';
	}
	if (w->actual_map[w->y_strip][w->x_strip] == 'D')
	{
		if (abs(w->y_strip - (int)w->y_pl) <= 1 && abs(w->x_strip - (int)w->x_pl) <= 1)
			w->actual_map[w->y_strip][w->x_strip] = 'O';
	}
}

double	get_WallCoef(double m_vector)
{
	double	coef;
	if (m_vector > 0)
		coef = MAX_ZOOM;
	else
		coef = -MAX_ZOOM;
	return(coef);
}

void	rotate_camera(t_info *w, int coef)
{
	double	saveDirX;
	double	savePlaneX;
	double	camMultiplier;

	camMultiplier = coef * CAM_SPEED;
	saveDirX = w->vectors.xPos;
	w->vectors.xPos = w->vectors.xPos * cos(camMultiplier) - w->vectors.yPos * sin(camMultiplier);
	w->vectors.yPos = saveDirX * sin(camMultiplier) + w->vectors.yPos * cos(camMultiplier);
	savePlaneX = w->vectors.xCam;
	w->vectors.xCam = w->vectors.xCam * cos(camMultiplier) - w->vectors.yCam * sin(camMultiplier);
	w->vectors.yCam = savePlaneX * sin(camMultiplier) + w->vectors.yCam * cos(camMultiplier);
}

// void	move_horizontaly(t_info *w, int direction)
// {
// 	double	stepX;
// 	double	stepY;
// 	char	c;
	
// 	stepX = w->vectors.xCam * w->player_speed * direction;
// 	stepY = w->vectors.yCam * w->player_speed * direction;
// 	c = w->actual_map[(int)(w->y_pl)][(int)(w->x_pl + stepX)];
// 	if(c != '1' && c != 'D')
// 		w->x_pl += stepX;
// 	c = w->actual_map[(int)(w->y_pl + (stepY))][(int)(w->x_pl)];
// 	if(c != '1' && c != 'D')
// 		w->y_pl += stepY;
// }

// void	move_verticaly(t_info *w, int direction)
// {
// 	double	stepX;
// 	double	stepY;
// 	char	c;
	
// 	stepX = w->vectors.xPos * w->player_speed * direction;
// 	stepY = w->vectors.yPos * w->player_speed * direction;
// 	c = w->actual_map[(int)(w->y_pl)][(int)(w->x_pl + stepX)];
// 	if(c != '1' && c != 'D')
// 		w->x_pl += stepX;
// 	c = w->actual_map[(int)(w->y_pl + (stepY))][(int)(w->x_pl)];
// 	if(c != '1' && c != 'D')
// 		w->y_pl += stepY;
// }

void	move_up(t_info *w, int dir)
{
	double	coef;
	double	stepX;
	double	stepY;
	char	c;
	
	stepX = w->vectors.xPos * w->player_speed * dir;
	stepY = w->vectors.yPos * w->player_speed * dir;
	coef = get_WallCoef(w->vectors.xPos) * dir;
	c = w->actual_map[(int)(w->y_pl)][(int)(w->x_pl +coef + stepX)];
	if(c != '1' && c != 'D')
	{
		w->x_pl += stepX;
	}
	coef = get_WallCoef(w->vectors.yPos) * dir;
	c = w->actual_map[(int)(w->y_pl +coef + stepY)][(int)(w->x_pl)];
	if(c != '1' && c != 'D')
	{
		w->y_pl += stepY;
	}
}

  void	move_down(t_info *w)
{	
	double	stepX;
	double	stepY;
	double	coef;
	char	c;

	stepX = w->vectors.xPos * w->player_speed;
	stepY = w->vectors.yPos * w->player_speed;
	coef = get_WallCoef(w->vectors.xPos);
	c = w->actual_map[(int)(w->y_pl ) ][(int)(w->x_pl -coef - stepX)];
	if(c != '1' && c != 'D')
	{
		w->x_pl -= stepX;
	}
	coef = get_WallCoef(w->vectors.yPos);
	c = w->actual_map[(int)(w->y_pl -coef - stepY)][(int)(w->x_pl)];
	if(c != '1' && c!= 'D')
	{
		w->y_pl -= stepY;
	}
}

void    move_right(t_info *w, int dir)
{
	double	stepX;
	double	stepY;
	double	coef;
	char	c;

	stepX = w->vectors.xCam * w->player_speed * dir;
	stepY = w->vectors.yCam * w->player_speed * dir;
	coef = get_WallCoef(w->vectors.xCam) * dir;
	c = w->actual_map[(int)(w->y_pl)][(int)(w->x_pl +coef +stepX)];
	if(c != '1' && c != 'D')
	{
		w->x_pl += stepX;
	}
	coef = get_WallCoef(w->vectors.yCam) * dir;
	c = w->actual_map[(int)(w->y_pl +coef + stepY)][(int)(w->x_pl)];
	if( c != '1' && c != 'D')
	{
		w->y_pl += stepY;
	}
}

void	move_left(t_info *w)
{
	double	stepX;
	double	stepY;
	double	coef;
	char	c;

	stepX = w->vectors.xCam * w->player_speed;
	stepY = w->vectors.yCam * w->player_speed;
	coef = get_WallCoef(w->vectors.xCam);
	c = w->actual_map[(int)(w->y_pl)][(int)(w->x_pl -coef -stepX)];
	if(c != '1' && c != 'D')
	{
		w->x_pl -= stepX;
	}
	coef = get_WallCoef(w->vectors.yCam);
	c = w->actual_map[(int)(w->y_pl -coef - stepY)][(int)(w->x_pl )];
	if( c != '1' && c!= 'D')
	{
		w->y_pl -= stepY;
	}
}

void	move_player(t_info *w)
{
	if (w->p_inputs.going_up == true)
		move_up(w, 1);
	if (w->p_inputs.going_down == true)
		move_up(w, -1);
	if (w->p_inputs.going_left == true)
		move_right(w, -1);
	if (w->p_inputs.going_right == true)
		move_right(w, 1);
	if (w->p_inputs.rotate_cam != 0)
		rotate_camera(w, w->p_inputs.rotate_cam);
}

// void	move_player(t_info *w)
// {
// 	if (w->p_inputs.going_up == true)
// 		move_verticaly(w, 1);
// 	if (w->p_inputs.going_down == true)
// 		move_verticaly(w, -1);
// 	if (w->p_inputs.going_left == true)
// 		move_horizontaly(w, -1);
// 	if (w->p_inputs.going_right == true)
// 		move_horizontaly(w, 1);
// 	if (w->p_inputs.rotate_cam != 0)
// 		rotate_camera(w, w->p_inputs.rotate_cam);
// }

int	deal_key(int id_key, t_info *w)
{
	if (id_key == XK_Escape)
		free_window(w);
	if (id_key == XK_e)
		check_doors(w);
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


