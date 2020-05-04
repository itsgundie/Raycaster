#include "../includes/wolf3d.h"

void	set_mouse(t_wolfec *w)
{
	SDL_SetRelativeMouseMode(SDL_ENABLE);
	SDL_WarpMouseInWindow(w->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	return ;
}

int		key_eater(t_wolfec *w, SDL_Event event, const Uint8 *keyboard_state)
{
	if (keyboard_state[SDL_SCANCODE_LSHIFT])
		w->player.mov_speed = MOVESPEED * 2;
	if (keyboard_state[SDL_SCANCODE_ESCAPE])
		return (0);
	return(1);
}

void		mouse_click(t_wolfec *w, SDL_Event event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
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

void		mouse_crawl(t_wolfec *w, SDL_Event event)
{
	if (w->mouse_in_win_flag == 0)
		SDL_SetRelativeMouseMode(SDL_DISABLE);
	else
	{
		if (event.motion.xrel != 0)
			w->player.angle -= event.motion.xrel * w->player.rot_speed;
		set_mouse(w);
	}
	return ;
}

int			events(t_wolfec *w)
{
	SDL_Event	event;
	const Uint8	*keyboard_state;

	while (SDL_PollEvent(&event))
	{
		keyboard_state = SDL_GetKeyboardState(NULL);
		if (event.type == SDL_KEYDOWN)
		 	if (!(key_eater(w, event, keyboard_state)))
				return (0);
		if (event.type == SDL_MOUSEBUTTONDOWN)
			mouse_click(w, event);
		if (event.type == SDL_MOUSEMOTION)
			mouse_crawl(w, event);
	}
	move_or_die(w, keyboard_state);
	return(1);
}