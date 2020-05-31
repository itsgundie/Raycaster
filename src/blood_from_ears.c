/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blood_from_ears.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amargy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 14:05:23 by amargy            #+#    #+#             */
/*   Updated: 2020/05/13 19:10:21 by amargy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	play_step(t_wolf3d *blazko)
{
	int r;

	r = 0;
	srand(time(NULL));
	while (r == 0)
		r = rand() % 6;
	if (!Mix_Playing(2))
	{
		if (r == 1)
			Mix_PlayChannel(2, blazko->sound.s1, 0);
		if (r == 2)
			Mix_PlayChannel(2, blazko->sound.s2, 0);
		if (r == 3)
			Mix_PlayChannel(2, blazko->sound.s3, 0);
		if (r == 4)
			Mix_PlayChannel(2, blazko->sound.s4, 0);
		if (r == 5)
			Mix_PlayChannel(2, blazko->sound.s5, 0);
		if (r == 6)
			Mix_PlayChannel(2, blazko->sound.s6, 0);
	}
}

void	stop_step(t_wolf3d *blazko)
{
	if (blazko->player.walk_direction == 0
	&& blazko->player.walk_direction == 0
	&& blazko->player.turn_direction == 0
	&& blazko->player.turn_direction == 0)
		Mix_FadeOutChannel(2, 200);
}

void	music_on(t_wolf3d *blazko)
{
	blazko->sound.badmusic = NULL;
	if (Mix_OpenAudio(41000, MIX_DEFAULT_FORMAT, 2, 512))
		ft_error("very bad music");
	blazko->sound.badmusic = Mix_LoadMUS("sound/music.ogg");
	blazko->sound.s1 = Mix_LoadWAV("sound/steps/1.ogg");
	blazko->sound.s2 = Mix_LoadWAV("sound/steps/2.ogg");
	blazko->sound.s3 = Mix_LoadWAV("sound/steps/3.ogg");
	blazko->sound.s4 = Mix_LoadWAV("sound/steps/4.ogg");
	blazko->sound.s5 = Mix_LoadWAV("sound/steps/5.ogg");
	blazko->sound.s6 = Mix_LoadWAV("sound/steps/6.ogg");
	if (blazko->sound.badmusic == NULL
	|| blazko->sound.s1 == NULL
	|| blazko->sound.s2 == NULL
	|| blazko->sound.s3 == NULL
	|| blazko->sound.s4 == NULL
	|| blazko->sound.s5 == NULL
	|| blazko->sound.s6 == NULL)
		ft_error("very bad music");
	Mix_AllocateChannels(23);
	Mix_VolumeMusic(30);
}
