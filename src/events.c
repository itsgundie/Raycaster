#include "../includes/wolf3d.h"

void	set_mouse(t_wolfec *w)
{
	SDL_SetRelativeMouseMode(SDL_ENABLE);
	SDL_WarpMouseInWindow(w->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	return ;
}

void	key_eater(t_wolfec *w)
{
	if (w->keyboard_state[SDL_SCANCODE_LSHIFT])
		w->player.mov_speed = fabs(MOVESPEED) * 2;
	if (w->keyboard_state[SDL_SCANCODE_ESCAPE])
		w->event.type = SDL_QUIT;
	return ;
}

void		mouse_click(t_wolfec *w)
{
	if (w->event.button.button == SDL_BUTTON_LEFT)
	{
		if (w->mouse_in_win_flag == 1)
		{
			SDL_SetRelativeMouseMode(SDL_DISABLE);
			w->mouse_in_win_flag = 0;
		}
		else
			w->mouse_in_win_flag = 1;
	}	
		return ;
}

void		mouse_crawl(t_wolfec *w)
{
	if (w->mouse_in_win_flag == 1)
	{
		if (w->event.motion.xrel != 0)
			w->player.angle -= w->event.motion.xrel * w->player.rot_speed;
	}
	return ;
}

void	events(t_wolfec *w)
{
	while (SDL_PollEvent(&w->event))
	{
		w->keyboard_state = SDL_GetKeyboardState(NULL);
		if (w->event.type == SDL_KEYDOWN)
		 	key_eater(w);
		if (w->event.type == SDL_MOUSEBUTTONDOWN)
			mouse_click(w);
		if (w->event.type == SDL_MOUSEMOTION)
			mouse_crawl(w);
	}
	return ;
}