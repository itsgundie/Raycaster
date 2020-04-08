
#include "../includes/wolf3d.h"



void			display(t_wolfec *w)
{
	SDL_Event	event;
	const Uint8	*keyboard_state;

	SDL_SetRelativeMouseMode(SDL_ENABLE);
	SDL_WarpMouseInWindow(w->win, WIDTH / 2, HEIGHT / 2);
	while (1)
	{
		while (SDL_PollEvent(&event))
		{
			keyboard_state = SDL_GetKeyboardState(NULL);
			if (event.type == SDL_KEYDOWN)
				key_event(keyboard_state, w);
		}
		if (event.type == SDL_QUIT || key_event(keyboard_state, w))
		 	break ;
		SDL_RenderCopy(w->rend, w->back, NULL, NULL);
		SDL_RenderPresent(w->rend);
	}
}