#include "../includes/wolf3d.h"

void	set_mouse(t_wolfec *w)
{
	SDL_SetRelativeMouseMode(SDL_ENABLE);
	SDL_WarpMouseInWindow(w->win, WIDTH / 2, HEIGHT / 2);
}

void	key_eater(t_wolfec *w, SDL_Event *event, const Uint8 *keyboard_state)
{
	if (keyboard_state[SDL_SCANCODE_LSHIFT])
		w->pos.mov_speed = fabs(MOVESPEED) * 2;
	if (keyboard_state[SDL_SCANCODE_ESCAPE])
		event->type = SDL_QUIT;
}

void	events(t_wolfec *w, SDL_Event *event, const Uint8 *keyboard_state)
{
	while (SDL_PollEvent(event))
	{
		keyboard_state = SDL_GetKeyboardState(NULL);
		if (event->type == SDL_KEYDOWN)
		 	key_eater(w, event, keyboard_state);
	}
}

B

