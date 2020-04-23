#include "../includes/wolf3d.h"

void	move(t_wolfec *w, const Uint8 *keyboard_state)
{
	float		cosine;
	float		sinus;
	float		rads;

	rads = degrees_to_rads(w->player.angle);
	cosine = cos(rads);
	sinus = sin(rads);
	forward_back(w, keyboard_state, cosine, sinus);
	left_right(w, keyboard_state, cosine, sinus);
}

void			forward_back(t_wolfec *w, const Uint8 *keyboard_state, float cosine, float sinus)
{	float	x;
	float 	y;
	float 	speed;

	x = w->player.pos_float.x;
	y = w->player.pos_float.y;
	speed = w->player.mov_speed;
	if (keyboard_state[SDL_SCANCODE_S] || keyboard_state[SDL_SCANCODE_DOWN])
	{
		if (!w->map[(int)y][(int)(x - cosine * speed)])  
			w->player.pos_float.x -= cosine * speed;
		if (!w->map[(int)(y - sinus * speed)][(int)x])
			w->player.pos_float.y -= sinus * speed;
	}
	if (keyboard_state[SDL_SCANCODE_W] || keyboard_state[SDL_SCANCODE_UP])
	{
		if (!w->map[(int)y][(int)(x + cosine * speed)])
			w->player.pos_float.x += cosine * speed;
		if (!w->map[(int)(y + sinus * speed)][(int)x])
			w->player.pos_float.y += sinus * speed;
	}
}

void			left_right(t_wolfec *w, const Uint8 *keyboard_state, float cosine, float sinus)
{
	float	x;
	float 	y;
	float 	speed;

	x = w->player.pos_float.x;
	y = w->player.pos_float.y;
	speed = w->player.mov_speed;
	if (keyboard_state[SDL_SCANCODE_D] || keyboard_state[SDL_SCANCODE_RIGHT])
	{
		if (!w->map[(int)(y - cosine * speed)][(int)x])
			w->player.pos_float.y -= cosine * speed;
		if (!w->map[(int)y][(int)(x + sinus * speed)])
			w->player.pos_float.x += sinus * speed;
	}
	if (keyboard_state[SDL_SCANCODE_A] || keyboard_state[SDL_SCANCODE_LEFT])
	{
		if (!w->map[(int)(y - cosine * speed)][(int)x])
			w->player.pos_float.y += cosine * speed;
		if (!w->map[(int)y][(int)(x + sinus * speed)])
			w->player.pos_float.x -= sinus * speed;
	}
}