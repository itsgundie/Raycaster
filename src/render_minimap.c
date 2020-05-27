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

void	render_rectangle(t_wolf3d *blazko, int tile_y, int tile_x, int color)
{
	int start_y;
	int start_x;
	int	end_y;
	int	end_x;

	start_y = tile_y * TILE_SIZE * MINIMAP_SCALE;
	start_x = tile_x * TILE_SIZE * MINIMAP_SCALE;
	end_y = start_y + TILE_SIZE * MINIMAP_SCALE;
	end_x = start_x + TILE_SIZE * MINIMAP_SCALE;
	while (++start_y < end_y)
	{
		while (++start_x < end_x)
			blazko->color_buffer[(start_y * WIN_WIDTH) + start_x] = color;
		start_x = tile_x * TILE_SIZE * MINIMAP_SCALE;
	}
}

void	render_line(t_wolf3d *blazko, t_v2int start, int end_x, int end_y)
{
	t_v2		delta;
	t_v2		sign;
	t_counters	error;

	delta.x = abs(end_x - start.x);
	delta.y = abs(end_y - start.y);
	sign.x = start.x < end_x ? 1 : -1;
	sign.y = start.y < end_y ? 1 : -1;
	error.i = delta.x - delta.y;
	blazko->color_buffer[(end_y * WIN_WIDTH) + end_x] = 0xFF0000;
	while (start.x != end_x || start.y != end_y)
	{
		blazko->color_buffer[(start.y * WIN_WIDTH) + start.x] = 0xFF0000;
		error.i2 = error.i * 2;
		if (error.i2 > -delta.y)
		{
			error.i -= delta.y;
			start.x += sign.x;
		}
		if (error.i2 < delta.x)
		{
			error.i += delta.x;
			start.y += sign.y;
		}
	}
}

void	render_rays(t_wolf3d *blazko)
{
	int		q;
	t_v2int	pos;

	q = -1;
	SDL_SetRenderDrawColor(blazko->render, 255, 0, 0, 255);
	pos.x = blazko->player.pos.x * MINIMAP_SCALE;
	pos.y = blazko->player.pos.y * MINIMAP_SCALE;
	while (++q < WIN_WIDTH)
	{
		render_line(blazko, pos,
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
			tile_color = blazko->map.map[tile_y][tile_x] == 1 ?
			0xFFFFFF : 000000;
			render_rectangle(blazko, tile_y, tile_x, tile_color);
		}
	}
}
