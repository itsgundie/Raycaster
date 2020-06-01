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

void	more_destruction(t_wolf3d *blazko, int q)
{
	q = 0;
	free(blazko->color_buffer);
	blazko->color_buffer = NULL;
	Mix_FreeChunk(blazko->sound.s1);
	Mix_FreeChunk(blazko->sound.s2);
	Mix_FreeChunk(blazko->sound.s3);
	Mix_FreeChunk(blazko->sound.s4);
	Mix_FreeChunk(blazko->sound.s5);
	Mix_FreeChunk(blazko->sound.s6);
	free(blazko->map.map);
	Mix_FreeMusic(blazko->sound.badmusic);
	Mix_Quit();
	SDL_DestroyTexture(blazko->color_tex);
	SDL_DestroyRenderer(blazko->render);
	SDL_DestroyWindow(blazko->window);
	ft_memset((void*)blazko, 0, sizeof(t_wolf3d));
	free(blazko);
	blazko = NULL;
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
