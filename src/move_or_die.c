#include "../includes/wolf3d.h"

void	move_or_die(t_wolfec *w, const Uint8 *keyboard_state)
{
	float		cosine;
	float		sinus;
	float		rads;

	rads = degrees_to_rads(w->player.angle);
	cosine = cos(rads);
	sinus = sin(rads);
	forward_back(w, cosine, sinus, keyboard_state);
	left_right(w, cosine, sinus, keyboard_state);
}

void			forward_back(t_wolfec *w, float cosine, float sinus, const Uint8 *keyboard_state)
{	
	int		x;
	int 	y;
	int 	speed;

	x = w->player.pos.x;
	y = w->player.pos.y;
	speed = w->player.mov_speed;
	if (keyboard_state[SDL_SCANCODE_W] || keyboard_state[SDL_SCANCODE_UP])
	{
		if (!w->map[y/TILE_SIZE][(int)(x + cosine * speed)/TILE_SIZE])
		{
			//printf("%d ", w->player.pos.x);
			w->player.pos.x += (int)(cosine * speed);
		}
		if (!w->map[(int)(y + sinus * speed)/TILE_SIZE][x/TILE_SIZE])
			w->player.pos.y += (int)(sinus * speed);
	}
	if (keyboard_state[SDL_SCANCODE_S] || keyboard_state[SDL_SCANCODE_DOWN])
	{
		if (!w->map[y/TILE_SIZE][((int)(x - cosine * speed))/TILE_SIZE])
		{
			printf("%d ", w->player.pos.x);
			w->player.pos.x -= (int)(cosine * speed);
		}
		if (!w->map[(int)(y - sinus * speed)/TILE_SIZE][x/TILE_SIZE])
			w->player.pos.y -= (int)(sinus * speed);
	}
}

void			left_right(t_wolfec *w, float cosine, float sinus, const Uint8 *keyboard_state)
{
	int		x;
	int 	y;
	float 	speed;

	x = w->player.pos.x;
	y = w->player.pos.y;
	speed = w->player.mov_speed;
	if (keyboard_state[SDL_SCANCODE_A] || keyboard_state[SDL_SCANCODE_LEFT])
	{
		if (!w->map[(int)(y - cosine * speed)/TILE_SIZE][x/TILE_SIZE])
			w->player.pos.y += (int)(cosine * speed);
		if (!w->map[y/TILE_SIZE][(int)(x + sinus * speed)/TILE_SIZE])
			w->player.pos.x -= (int)(sinus * speed);
	}
	if (keyboard_state[SDL_SCANCODE_D] || keyboard_state[SDL_SCANCODE_RIGHT])
	{
		if (!w->map[(int)(y - cosine * speed)/TILE_SIZE][x/TILE_SIZE])
			w->player.pos.y -= (int)(cosine * speed);
		if (!w->map[y/TILE_SIZE][(int)(x + sinus * speed)/TILE_SIZE])
			w->player.pos.x += (int)(sinus * speed);
	}
}