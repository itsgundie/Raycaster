/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amargy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 10:04:13 by amargy            #+#    #+#             */
/*   Updated: 2020/05/15 11:12:21 by amargy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	render_rectangle(t_wolf3d *blazko, int tile_y, int tile_x)
{
	int start_y = tile_y * TILE_SIZE * MINIMAP_SCALE - 1;
	int start_x = tile_x * TILE_SIZE * MINIMAP_SCALE - 1;
	int	end_y = start_y + TILE_SIZE * MINIMAP_SCALE;
	int	end_x = start_x + TILE_SIZE * MINIMAP_SCALE;
	while (++start_y < end_y)
	{
		while (++start_x < end_x)
			SDL_RenderDrawPoint(blazko->render, start_x, start_y);
		start_x = tile_x * TILE_SIZE * MINIMAP_SCALE;
	}
}

void	render_line(t_wolf3d *blazko, int start_x, int start_y, int end_x, int end_y)
{
	int deltaX = abs(end_x - start_x);
    int deltaY = abs(end_y - start_y);
    int signX = start_x < end_x ? 1 : -1;
    int signY = start_y < end_y ? 1 : -1;
    int error = deltaX - deltaY;
	int error2;
	SDL_RenderDrawPoint(blazko->render, end_x, end_y);
    while(start_x != end_x || start_y != end_y) 
   {
        SDL_RenderDrawPoint(blazko->render, start_x, start_y);
        error2 = error * 2;
        if(error2 > -deltaY) 
        {
            error -= deltaY;
            start_x += signX;
        }
        if(error2 < deltaX) 
        {
            error += deltaX;
            start_y += signY;
        }
    }
}

void	render_rays(t_wolf3d *blazko)
{
	int q;

	q = -1;
	SDL_SetRenderDrawColor(blazko->render, 255, 0, 0, 255);
	while (++q < WIN_WIDTH)
	{
		render_line(blazko,
			blazko->player.pos.x * MINIMAP_SCALE,
			blazko->player.pos.y * MINIMAP_SCALE,
			blazko->rays[q].wall_hit.x * MINIMAP_SCALE,
			blazko->rays[q].wall_hit.y * MINIMAP_SCALE);
	}
}

void	render_map(t_wolf3d *blazko)
{
	int tile_y;
	int tile_x;
	int tile_color;

	tile_y = -1;
	while (++tile_y < blazko->map.rows)
	{
		tile_x = -1;
		while (++tile_x < blazko->map.columns)
		{
			tile_color = blazko->map.map[tile_y][tile_x] == 1 ? 255 : 0;
			SDL_SetRenderDrawColor(blazko->render, tile_color, tile_color, tile_color, 255);
			render_rectangle(blazko, tile_y, tile_x);
		}
	}
}