/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amargy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 12:05:34 by amargy            #+#    #+#             */
/*   Updated: 2020/05/14 13:14:23 by amargy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	music_on_off(t_wolf3d *blazko)
{
	if (blazko->sound.is_m == 0)
	{
		blazko->sound.is_m = 1;
		Mix_PlayMusic(blazko->sound.badmusic, 15);
	}
	else
	{
		blazko->sound.is_m = 0;
		Mix_FadeOutMusic(500);
	}
}

int		key_down(t_wolf3d *blazko, SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_m)
		music_on_off(blazko);
	if (event.key.keysym.sym == SDLK_ESCAPE)
		return (0);
	if (event.key.keysym.sym == SDLK_UP)
	{
		blazko->player.walk_direction = +1;
		play_step(blazko);
	}
	if (event.key.keysym.sym == SDLK_DOWN)
	{
		blazko->player.walk_direction = -1;
		play_step(blazko);
	}
	if (event.key.keysym.sym == SDLK_RIGHT)
	{
		blazko->player.turn_direction = +1;
		play_step(blazko);
	}
	if (event.key.keysym.sym == SDLK_LEFT)
	{
		blazko->player.turn_direction = -1;
		play_step(blazko);
	}
	return (1);
}

void	key_up(t_wolf3d *blazko, SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_UP)
	{
		blazko->player.walk_direction = 0;
		stop_step(blazko);
	}
	if (event.key.keysym.sym == SDLK_DOWN)
	{
		blazko->player.walk_direction = 0;
		stop_step(blazko);
	}
	if (event.key.keysym.sym == SDLK_RIGHT)
	{
		blazko->player.turn_direction = 0;
		stop_step(blazko);
	}
	if (event.key.keysym.sym == SDLK_LEFT)
	{
		blazko->player.turn_direction = 0;
		stop_step(blazko);
	}
}

int		put_in(t_wolf3d *blazko)
{
	SDL_Event event;

	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT)
		return (0);
	else if (event.type == SDL_KEYDOWN)
	{
		if (!(key_down(blazko, event)))
			return (0);
	}
	else if (event.type == SDL_KEYUP)
		key_up(blazko, event);
	return (1);
}
