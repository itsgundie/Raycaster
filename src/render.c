
#include "../includes/wolf3d.h"

void	render_it(t_wolfec *w)
{
	SDL_RenderCopy(w->rend, w->back, NULL, NULL);
	SDL_RenderPresent(w->rend);
}