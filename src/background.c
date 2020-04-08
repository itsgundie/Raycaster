
#include "../includes/wolf3d.h"


void	verx(t_wolfec *w)
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
			SDL_SetRenderDrawColor(w->rend, color / 10, color / 1.2, color, 255);
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
			SDL_SetRenderDrawColor(w->rend, color, color, color, 255);
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
