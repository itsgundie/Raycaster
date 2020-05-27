/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cspare <cspare@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 23:48:52 by cspare            #+#    #+#             */
/*   Updated: 2020/05/28 01:19:39 by cspare           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

uint32_t		make_darkness(uint32_t color, float depf, int vert, int disco)
{
	t_argb		palet;
	uint32_t	disco_move;

	if (disco)
	{
		depf = 1.0f - depf;
		vert ? depf -= 0.1 : depf;
		palet.a = ((color >> 24) & 0xFF);
		palet.r = (((color >> 16) & 0xFF) / depf * 2);
		palet.g = (((color >> 8) & 0xFF) / depf * 0.5f);
		palet.b = ((color & 0xFF) / depf * 0.33f);
		return ((palet.a << 24) | (palet.r << 16) | (palet.g << 8) | palet.b);
	}
	if (color == 0 || depf > 0.9f)
		return (0);
	if (depf <= 0.0f)
		return (color);
	depf = 1.0f - depf;
	vert ? depf -= 0.1 : depf;
	palet.a = ((color >> 24) & 0xFF);
	palet.r = (((color >> 16) & 0xFF) * depf);
	palet.g = (((color >> 8) & 0xFF) * depf);
	palet.b = ((color & 0xFF) * depf);
	return ((palet.a << 24) | (palet.r << 16) | (palet.g << 8) | palet.b);
}

void			render(t_wolf3d *blazko)
{
	SDL_SetRenderDrawColor(blazko->render, 0, 0, 0, 255);
	SDL_RenderClear(blazko->render);
	make3d(blazko);
	render_map(blazko);
	render_rays(blazko);
	render_color_buf(blazko);
	clear_color_buf(blazko->color_buffer, 0xFF333333);
	SDL_RenderPresent(blazko->render);
	stop_step(blazko);
}
