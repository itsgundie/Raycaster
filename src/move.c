#include "../includes/wolf3d.h"

void	move(t_wolfec *w)
{
	float		cosine;
	float		sinus;
	float		rads;

	cosine = cos(w->player.angle);
	sinus = sin(w->player.angle);
	forward_back(w, cosine, sinus);
	left_right(w, cosine, sinus);
	//printf("ang:%f ", w->player.angle);
}

void			forward_back(t_wolfec *w, float cosine, float sinus)
{	
	float	x;
	float 	y;
	int 	speed;

	x = (float)w->player.pos.x;
	y = (float)w->player.pos.y;
	speed = w->player.mov_speed;
	if (w->keyboard_state[SDL_SCANCODE_W] || w->keyboard_state[SDL_SCANCODE_UP])
	{
		// printf("x:%d ", w->player.pos.x);
		// printf("y:%d ", w->player.pos.y);
		// printf("ang:%f ", w->player.angle);
		if (!w->map[(int)(y/TILE_SIZE)][(int)(x + cosine * speed)/TILE_SIZE])
			w->player.pos.x += (int)(cosine * speed);
		if (!w->map[(int)(y + sinus * speed)/TILE_SIZE][(int)(x/TILE_SIZE)])
			w->player.pos.y += (int)(sinus * speed);
	}
	if (w->keyboard_state[SDL_SCANCODE_S] || w->keyboard_state[SDL_SCANCODE_DOWN])
	{
		if (!w->map[(int)(y/TILE_SIZE)][((int)(x - cosine * speed))/TILE_SIZE])
			w->player.pos.x -= (int)(cosine * speed);
		if (!w->map[(int)(y - sinus * speed)/TILE_SIZE][(int)(x/TILE_SIZE)])
			w->player.pos.y -= (int)(sinus * speed);
	}
}

// void			forward_back(t_wolfec *w, float cosine, float sinus)
// {	
// 	float	x;
// 	float 	y;
// 	int 	speed;

// 	x = (float)w->player.pos.x;
// 	y = (float)w->player.pos.y;
// 	speed = w->player.mov_speed;
// 	if (w->keyboard_state[SDL_SCANCODE_W] || w->keyboard_state[SDL_SCANCODE_UP])
// 	{
// 		if (!w->map[(int)(y/TILE_SIZE)][(int)(x + cosine * speed * (is_looking_left(&(w->player.angle)) ? -1 : 1))/TILE_SIZE])
// 			w->player.pos.x += ((int)(cosine * speed)) * (is_looking_left(&(w->player.angle)) ? -1 : 1);
// 		if (!w->map[(int)(y + sinus * speed * (is_looking_up(&(w->player.angle)) ? -1 : 1))/TILE_SIZE][(int)(x/TILE_SIZE)])
// 			w->player.pos.y += (int)(sinus * speed) * (is_looking_up(&(w->player.angle)) ? -1 : 1);
// 	}
// 	if (w->keyboard_state[SDL_SCANCODE_S] || w->keyboard_state[SDL_SCANCODE_DOWN])
// 	{
// 		if (!w->map[(int)(y/TILE_SIZE)][(int)(x - cosine * speed * (is_looking_left(&(w->player.angle)) ? -1 : 1))/TILE_SIZE])
// 			w->player.pos.x -= ((int)(cosine * speed)) * (is_looking_left(&(w->player.angle)) ? -1 : 1);
// 		if (!w->map[(int)(y - sinus * speed * (is_looking_up(&(w->player.angle)) ? -1 : 1))/TILE_SIZE][(int)(x/TILE_SIZE)])
// 			w->player.pos.y -= (int)(sinus * speed) * (is_looking_up(&(w->player.angle)) ? -1 : 1);
// 	}
// }

void			left_right(t_wolfec *w, float cosine, float sinus)
{
	float	x;
	float 	y;
	float 	speed;

	x = (float)w->player.pos.x;
	y = (float)w->player.pos.y;
	speed = w->player.mov_speed;
	if (w->keyboard_state[SDL_SCANCODE_A] || w->keyboard_state[SDL_SCANCODE_LEFT])
	{
		if (!w->map[(int)(y - cosine * speed)/TILE_SIZE][(int)(x/TILE_SIZE)])
			w->player.pos.y += (int)(cosine * speed);
		if (!w->map[(int)(y/TILE_SIZE)][(int)(x + sinus * speed)/TILE_SIZE])
			w->player.pos.x -= (int)(sinus * speed);
	}
	if (w->keyboard_state[SDL_SCANCODE_D] || w->keyboard_state[SDL_SCANCODE_RIGHT])
	{
		if (!w->map[(int)(y - cosine * speed)/TILE_SIZE][(int)(x/TILE_SIZE)])
			w->player.pos.y -= (int)(cosine * speed);
		if (!w->map[(int)(y/TILE_SIZE)][(int)(x + sinus * speed)/TILE_SIZE])
			w->player.pos.x += (int)(sinus * speed);
	}
}