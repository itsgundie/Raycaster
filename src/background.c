
#include "../includes/wolf3d.h"


void	verh(t_wolfec *w)
{
	int			y;
	int			x;
	int			color;

	color = 0;
	y = WIN_HEIGHT / 2;
	while (--y >= 0)
	{
		x = -1;
		while (++x <= WIN_WIDTH)
		{
			SDL_RenderDrawPoint(w->rend, x, y);
			SDL_SetRenderDrawColor(w->rend, color, 0, 0 , 255);
		}
		if (y % 2 == 0 && color < 200)
			color++;
	}
}

void	niz(t_wolfec *w)
{
	int			y;
	int			x;
	int			color;

	color = 0;
	y = WIN_HEIGHT / 2;
	while (++y <= WIN_HEIGHT)
	{
		x = -1;
		while (++x <= WIN_WIDTH)
		{
			SDL_RenderDrawPoint(w->rend, x, y);
			SDL_SetRenderDrawColor(w->rend, color / 40, 0, 0, 255);
		}
		if (y % 2 == 0 && color < 200)
			color++;
	}
}

void	predraw(t_wolfec *w)
{
	//SDL_SetRenderTarget(w->rend, w->back);
	SDL_SetRenderTarget(w->rend, NULL);
	//SDL_RenderClear(w->rend);
	verh(w);
	niz(w);
	//SDL_SetRenderTarget(w->rend, NULL);
	//SDL_RenderPresent(w->rend);	
}
