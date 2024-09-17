#include "cub3D.h"

void	moovetoFirstXY(t_info *w, double rayX, double rayY)
{
	if(rayX < 0)
	  {
		w->vectors.stepX = -1;
		w->vectors.nextDistX = (w->x_pl - w->current_map_x) * w->vectors.deltaX;
	  }
	  else
	  {
		w->vectors.stepX = 1;
		w->vectors.nextDistX = (w->current_map_x + 1.0 - w->x_pl) * w->vectors.deltaX;
	  }
	  if(rayY < 0)
	  {
		w->vectors.stepY = -1;
		w->vectors.nextDistY = (w->y_pl - w->current_map_y) * w->vectors.deltaY;
	  }
	  else
	  {
		w->vectors.stepY = 1;
		w->vectors.nextDistY = (w->current_map_y + 1.0 - w->y_pl) * w->vectors.deltaY;
	  }
}

int	applyDDA(t_info *w, int	wallDist)
{
	while(42)
	{
		if(w->vectors.nextDistX < w->vectors.nextDistY)
		{
			printf("moving on x..\n");
			w->vectors.nextDistX += w->vectors.deltaX;
			w->current_map_x += w->vectors.stepX;
			w->side = 0;
			// print_map_current(w->actual_map, w->current_map_x, w->current_map_y);
		}
		else
		{
			printf("moving on y..\n");
			w->vectors.nextDistY += w->vectors.deltaY;
			w->current_map_y += w->vectors.stepY;
			w->side = 1;
			// print_map_current(w->actual_map, w->current_map_x, w->current_map_y);
		}
		if(w->actual_map[w->current_map_y][w->current_map_x] == '1')
		{
			print_map_current(w->actual_map, w->current_map_x, w->current_map_y);
			printf("a wall was hit at x :%d, y:%d !\n\n", w->current_map_x, w->current_map_y);
			break;
		}
	}
	if(w->side == 0) 
		wallDist = (w->vectors.nextDistX - w->vectors.deltaX);
	else
		wallDist = (w->vectors.nextDistY - w->vectors.deltaY);
	return (wallDist);
}

void	getDrawLimits(double wallDist)
{
	int	lineHeight;
	int	drawStart;
	int	drawEnd;

	lineHeight = (int)(DEFAULT_HEIGHT / wallDist);
	//calculate lowest and highest pixel to fill in current stripe
	drawStart = -lineHeight / 2 + DEFAULT_HEIGHT / 2;
	if(drawStart < 0)
		drawStart = 0;
	drawEnd = lineHeight / 2 + DEFAULT_HEIGHT / 2;
	if(drawEnd >= DEFAULT_HEIGHT)
		drawEnd = DEFAULT_HEIGHT - 1;
}

int	getX_CoordTexture(t_info *w, int rayDirX, int rayDirY, int distWall)
{
	double	wallX; //where exactly the wall was hit
	int		texX;

	if(w->side == 0)
	  	wallX = w->y_pl + distWall * rayDirY;
	else
	  	wallX = w->x_pl + distWall * rayDirX;
	wallX -= floor((wallX));
		
	texX = wallX * (double)SPRITE_LENGTH; //x coordinate on the texture
	if(w->side == 0 && rayDirX > 0)
	  	texX = SPRITE_LENGTH - texX - 1;
	if(w->side == 1 && rayDirY < 0)
	  	texX = SPRITE_LENGTH - texX - 1;
	return (texX);
}

void	set_rays(t_info *w)
{
	double	rayDirX;
	double	rayDirY;
	double	cameraX;
	int		i;
	int		distWall;

	while(42)// to change ?
	{
		i = 0 ;
		while (i < DEFAULT_LENGTH)
		{
			printf("xPos is %f\n", w->vectors.xPos);
			printf("yPos is %f\n", w->vectors.yPos);
			cameraX = 2 * i / (double)DEFAULT_LENGTH - 1;
	  		rayDirX = w->vectors.xPos + w->vectors.xCam * cameraX;
	  		rayDirY = w->vectors.yPos + w->vectors.yCam * cameraX;
			///////////////
			w->current_map_x = (int)w->x_pl; // cast float into int
			w->current_map_y = (int)w->y_pl;
			///////////////
			if (rayDirX == 0)
			{
				printf("RayDirX is 0.\n");
				w->vectors.deltaX = 1e30;
			}
			else
				w->vectors.deltaX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
			if (rayDirY == 0)
			{
				printf("RayDirY is 0.\n");
				w->vectors.deltaY = 1e30;
			}
			else
				w->vectors.deltaY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
			//////////////
			moovetoFirstXY(w, rayDirX, rayDirY);
			distWall = applyDDA(w, 0);
			getDrawLimits(distWall);
			i++;
		}
		break ;
	}
}

