/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_everything.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cspare <cspare@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 15:20:42 by amargy            #+#    #+#             */
/*   Updated: 2020/06/02 23:22:04 by cspare           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	not_my_tempo(t_wolf3d *blazko)
{
	if (blazko->sound.s1)
		Mix_FreeChunk(blazko->sound.s1);
	if (blazko->sound.s2)
		Mix_FreeChunk(blazko->sound.s2);
	if (blazko->sound.s3)
		Mix_FreeChunk(blazko->sound.s3);
	if (blazko->sound.s4)
		Mix_FreeChunk(blazko->sound.s4);
	if (blazko->sound.s5)
		Mix_FreeChunk(blazko->sound.s5);
	if (blazko->sound.s6)
		Mix_FreeChunk(blazko->sound.s6);
	if (blazko->sound.badmusic)
		Mix_FreeMusic(blazko->sound.badmusic);
}

void	more_destruction(t_wolf3d *blazko, int q)
{
	q = 0;
	if (blazko->color_buffer)
		free(blazko->color_buffer);
	not_my_tempo(blazko);
	if (blazko->map.map)
		free(blazko->map.map);
	if (blazko->color_tex)
		SDL_DestroyTexture(blazko->color_tex);
	if (blazko->render)
		SDL_DestroyRenderer(blazko->render);
	if (blazko->window)
		SDL_DestroyWindow(blazko->window);
	if (blazko)
	{
		ft_memset((void*)blazko, 0, sizeof(t_wolf3d));
		free(blazko);
	}
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

void	destroy(t_wolf3d *blazko)
{
	int q;

	q = -1;
	while (++q < NUM_OF_TEXTURES)
	{
		if (blazko->surfs_for_texes[q])
			SDL_FreeSurface(blazko->surfs_for_texes[q]);
	}
	q = 0;
	if (blazko->map.map)
	{
		while (q < blazko->map.rows)
		{
			if (blazko->map.map[q])
				free(blazko->map.map[q]);
			q++;
		}
		more_destruction(blazko, q);
	}
}

int		error_exit(char *str, t_wolf3d *blazko)
{
	ft_printf("%s", str);
	destroy(blazko);
	exit(1);
}
