
#include "../includes/wolf3d.h"


void	verh(t_wolfec *w)
{
	int			y;
	int			x;
	int			color;

	color = 0;
	y = HEIGHT / 2;
	while (--y >= 0)
	{
		x = -1;
		while (++x <= WIDTH)
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
	y = HEIGHT / 2;
	while (++y <= HEIGHT)
	{
		x = -1;
		while (++x <= WIDTH)
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
	SDL_SetRenderTarget(w->rend, w->back);
	verx(w);
	niz(w);
	SDL_SetRenderTarget(w->rend, NULL);
}
