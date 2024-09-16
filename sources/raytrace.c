#include "../includes/parsing.h"

void	moovetoFirstXY(t_info *w, double rayX, double rayY)
{
	if(rayX < 0)
	  {
		w->vectors.stepX = -1;
		w->vectors.nextDistX = (w->vectors.x_pl - w->vectors.current_map_x) * w->vectors.deltaX;
	  }
	  else
	  {
		w->vectors.stepX = 1;
		w->vectors.nextDistX = (w->vectors.current_map_x + 1.0 - w->vectors.x_pl) * w->vectors.deltaX;
	  }
	  if(rayY < 0)
	  {
		w->vectors.stepY = -1;
		w->vectors.nextDistY = (w->vectors.y_pl - w->vectors.current_map_y) * w->vectors.deltaY;
	  }
	  else
	  {
		w->vectors.stepY = 1;
		w->vectors.nextDistY = (w->vectors.current_map_y + 1.0 - w->vectors.y_pl) * w->vectors.deltaY;
	  }
}

int	applyDDA(t_info *w, int side)
{
	int	wallDist;

	while(42)
	{
		printf("current x :%d, current y:%d !\n", w->vectors.current_map_x, w->vectors.current_map_y);
		printf("current nextDistX :%f, current nextDistY:%f !\n", w->vectors.nextDistX, w->vectors.nextDistY);
		if(w->vectors.nextDistX < w->vectors.nextDistY)
		{
			printf("X < Y !\n");
			printf("nextDistX + %f = %f !\n", w->vectors.deltaX, w->vectors.nextDistX + w->vectors.deltaX);
			printf("current_map_x + %d = %d !\n\n", w->vectors.stepX ,w->vectors.current_map_x + w->vectors.stepX);
			w->vectors.nextDistX += w->vectors.deltaX;
			w->vectors.current_map_x += w->vectors.stepX;
			side = 0;
		}
		else
		{
			printf("X > Y !\n");
			printf("nextDistY + %f = %f !\n", w->vectors.deltaY, w->vectors.nextDistY + w->vectors.deltaY);
			printf("current_map_y + %d = %d !\n\n", w->vectors.stepY ,w->vectors.current_map_y + w->vectors.stepY);
			w->vectors.nextDistY += w->vectors.deltaY;
			w->vectors.current_map_y += w->vectors.stepY;
			side = 1;
		}
		//Check if ray has hit a wall
		if(w->map_file[w->vectors.current_map_x][w->vectors.current_map_y] == '1')
		{
			printf("a wall was hit at x :%d, y:%d !\n\n", w->vectors.current_map_x, w->vectors.current_map_y);
			break;
		}
	}
	if(side == 0) 
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
			cameraX = 2 * i / (double)DEFAULT_LENGTH - 1;
	  		rayDirX = w->vectors.xPos + w->vectors.xCam * cameraX;
	  		rayDirY = w->vectors.yPos + w->vectors.yCam * cameraX;
			///////////////
			w->vectors.current_map_x = (int)w->vectors.x_pl; // cast float into int
			w->vectors.current_map_y = (int)w->vectors.y_pl;
			///////////////
			w->vectors.deltaX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
			w->vectors.deltaY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
			if (rayDirX == 0)
				w->vectors.deltaX = 1e30;
			if (rayDirY == 0)
				w->vectors.deltaY = 1e30;
			//////////////
			moovetoFirstXY(w, rayDirX, rayDirY);
			distWall = applyDDA(w, 0);
			getDrawLimits(distWall);
			break ; //comment
			i++;
		}
		break ;
	}
}

