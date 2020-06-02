/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_everything.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cspare <cspare@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 15:20:42 by amargy            #+#    #+#             */
/*   Updated: 2020/06/01 01:15:28 by cspare           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	not_my_tempo(t_wolf3d *blazko)
{
	if (blazko->sound.s1 != NULL)
		Mix_FreeChunk(blazko->sound.s1);
	if (blazko->sound.s2 != NULL)
		Mix_FreeChunk(blazko->sound.s2);
	if (blazko->sound.s3 != NULL)
		Mix_FreeChunk(blazko->sound.s3);
	if (blazko->sound.s4 != NULL)
		Mix_FreeChunk(blazko->sound.s4);
	if (blazko->sound.s5 != NULL)
		Mix_FreeChunk(blazko->sound.s5);
	if (blazko->sound.s6 != NULL)
		Mix_FreeChunk(blazko->sound.s6);
	if (blazko->sound.badmusic != NULL)
		Mix_FreeMusic(blazko->sound.badmusic);
}

void	more_destruction(t_wolf3d *blazko, int q)
{
	q = 0;
	if (blazko != NULL && blazko->color_buffer != NULL)
	{
		free(blazko->color_buffer);
		blazko->color_buffer = NULL;
	}
	not_my_tempo(blazko);
	if (blazko->map.map != NULL)
		free(blazko->map.map);
	if (blazko->color_tex != NULL)
		SDL_DestroyTexture(blazko->color_tex);
	if (blazko->render != NULL)
		SDL_DestroyRenderer(blazko->render);
	if (blazko->window != NULL)
		SDL_DestroyWindow(blazko->window);
	if (blazko != NULL)
	{
		ft_memset((void*)blazko, 0, sizeof(t_wolf3d));
		free(blazko);
		blazko = NULL;
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
		SDL_FreeSurface(blazko->surfs_for_texes[q]);
		blazko->surfs_for_texes[q] = NULL;
		blazko->textures[q] = NULL;
	}
	while (blazko->params_vars.params_list != NULL)
	{
		blazko->params_vars.tmp = blazko->params_vars.params_list->next;
		free(blazko->params_vars.params_list->line);
		free(blazko->params_vars.params_list);
		blazko->params_vars.params_list = blazko->params_vars.tmp;
	}
	q = 0;
	while (q < blazko->map.rows)
	{
		free(blazko->map.map[q]);
		q++;
	}
	more_destruction(blazko, q);
}

int		error_exit(char *str, t_wolf3d *blazko)
{
	ft_printf("%s", str);
	destroy(blazko);
	exit(1);
}
