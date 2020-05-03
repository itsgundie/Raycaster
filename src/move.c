#include "../includes/wolf3d.h"

void	move(t_wolfec *w)
{
	float		cosine;
	float		sinus;
	float		rads;

	rads = degrees_to_rads(w->player.angle);
	cosine = cos(rads);
	sinus = sin(rads);
	forward_back(w, cosine, sinus);
	left_right(w, cosine, sinus);
}

void			forward_back(t_wolfec *w, float cosine, float sinus)
{	int	x;
	int 	y;
	int 	speed;

	x = w->player.pos.x;
	y = w->player.pos.y;
	speed = w->player.mov_speed;
	if (w->keyboard_state[SDL_SCANCODE_S] || w->keyboard_state[SDL_SCANCODE_DOWN])
	{
		if (!w->map[y/TILE_SIZE][((int)(x - cosine * speed))/TILE_SIZE])  
			w->player.pos.x -= (int)(cosine * speed);
		if (!w->map[(int)(y - sinus * speed)/TILE_SIZE][x/TILE_SIZE])
			w->player.pos.y -= (int)(sinus * speed);
	}
	if (w->keyboard_state[SDL_SCANCODE_W] || w->keyboard_state[SDL_SCANCODE_UP])
	{
		if (!w->map[y/TILE_SIZE][(int)(x + cosine * speed)/TILE_SIZE])
			w->player.pos.x += (int)(cosine * speed);
		if (!w->map[(int)(y + sinus * speed)/TILE_SIZE][x/TILE_SIZE])
			w->player.pos.y += (int)(sinus * speed);
	}
}

void			left_right(t_wolfec *w, float cosine, float sinus)
{
	int		x;
	int 	y;
	float 	speed;

	x = w->player.pos.x;
	y = w->player.pos.y;
	speed = w->player.mov_speed;
	if (w->keyboard_state[SDL_SCANCODE_D] || w->keyboard_state[SDL_SCANCODE_RIGHT])
	{
		if (!w->map[(int)(y - cosine * speed)/TILE_SIZE][x/TILE_SIZE])
			w->player.pos.y -= (int)(cosine * speed);
		if (!w->map[y/TILE_SIZE][(int)(x + sinus * speed)/TILE_SIZE])
			w->player.pos.x += (int)(sinus * speed);
	}
	if (w->keyboard_state[SDL_SCANCODE_A] || w->keyboard_state[SDL_SCANCODE_LEFT])
	{
		if (!w->map[(int)(y - cosine * speed)/TILE_SIZE][x/TILE_SIZE])
			w->player.pos.y += (int)(cosine * speed);
		if (!w->map[y/TILE_SIZE][(int)(x + sinus * speed)/TILE_SIZE])
			w->player.pos.x -= (int)(sinus * speed);
	}
}