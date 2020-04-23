#include "../includes/wolf3d.h"

void	set_mouse(t_wolfec *w)
{
	SDL_SetRelativeMouseMode(SDL_ENABLE);
	SDL_WarpMouseInWindow(w->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
}

void	key_eater(t_wolfec *w, SDL_Event *event, const Uint8 *keyboard_state)
{
	if (keyboard_state[SDL_SCANCODE_LSHIFT])
		w->player.mov_speed = fabs(MOVESPEED) * 2;
	if (keyboard_state[SDL_SCANCODE_ESCAPE])
		event->type = SDL_QUIT;
}

void		mouse_click(SDL_Event *event, t_wolfec *w)
{
	if (event->button.button == SDL_BUTTON_LEFT)
		if (w->mouse_in_win_flag == 1)
		{
			SDL_SetRelativeMouseMode(SDL_DISABLE);
			w->mouse_in_win_flag = 0;
		}
		else
			w->mouse_in_win_flag = 1;
}

void		mouse_crawl(SDL_Event *event, t_wolfec *w)
{
	if (w->mouse_in_win_flag == 1)
	{
		if (event->motion.xrel != 0)
			w->player.angle -= event->motion.xrel * w->player.rot_speed;
	}
}

void	events(t_wolfec *w, SDL_Event *event, const Uint8 *keyboard_state)
{
	while (SDL_PollEvent(event))
	{
		keyboard_state = SDL_GetKeyboardState(NULL);
		if (event->type == SDL_KEYDOWN)
		 	key_eater(w, event, keyboard_state);
		if (event->type == SDL_MOUSEBUTTONDOWN)
			mouse_click(event, w);
		if (event->type == SDL_MOUSEMOTION)
			mouse_crawl(event, w);
	}
}