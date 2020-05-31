/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_everything.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amargy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 15:20:42 by amargy            #+#    #+#             */
/*   Updated: 2020/05/13 13:12:34 by amargy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	destroy(t_wolf3d *blazko)
{
	int q;
	int *tmp;

	q = NUM_OF_TEXTURES;
	free(blazko->color_buffer);
	blazko->color_buffer = NULL;
	while (--q >= 0)
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
	free(blazko->map.map);
	free(blazko);
	Mix_FreeMusic(blazko->sound.badmusic);
	Mix_Quit();
	SDL_DestroyTexture(blazko->color_tex);
	SDL_DestroyRenderer(blazko->render);
	SDL_DestroyWindow(blazko->window);
	IMG_Quit();
	SDL_Quit();
}

int		error_exit(char *str, t_wolf3d *blazko)
{
	printf("%s", str);
	destroy(blazko);
	exit(1);
}