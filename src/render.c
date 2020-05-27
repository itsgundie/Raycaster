#include "../includes/wolf3d.h"

uint32_t	make_darkness(uint32_t color, float intensity,
									int is_vertical, int disco)
{
	t_argb		palet;
	uint32_t	disco_move;

	if (disco)
	{
		intensity = 1.0f - intensity;
		is_vertical ? intensity -= 0.1 : intensity;
		palet.a = ((color >> 24) & 0xFF);
		palet.r = (((color >> 16) & 0xFF) / intensity * 2);
		palet.g = (((color >> 8) & 0xFF) / intensity * 0.5f);
		palet.b = ((color & 0xFF) / intensity * 0.33f);
		return ((palet.a << 24) | (palet.r << 16) | (palet.g << 8) | palet.b);
	}
	if (color == 0 || intensity > 0.9f)
		return (0);
	if (intensity <= 0.0f)
		return (color);
	intensity = 1.0f - intensity;
	is_vertical ? intensity -= 0.1 : intensity;
	palet.a = ((color >> 24) & 0xFF);
	palet.r = (((color >> 16) & 0xFF) * intensity);
	palet.g = (((color >> 8) & 0xFF) * intensity);
	palet.b = ((color & 0xFF) * intensity);
	return ((palet.a << 24) | (palet.r << 16) | (palet.g << 8) | palet.b);
}

void	make3d(t_wolf3d *blazko)
{
	int		q;
	int		y;
	float	dist_to_proj_plane;
	float	perp_dist;

	q = -1;
	dist_to_proj_plane = (WIN_WIDTH / 2) / tan(blazko->player.fov / 2);
	while (++q < RAYS_NUM)
	{
		perp_dist = blazko->rays[q].distance *
			cos(blazko->rays[q].angle - blazko->player.rot_angle);
		blazko->rays[q].wall_height = (int)((TILE_SIZE / perp_dist) * dist_to_proj_plane);
		blazko->rays[q].draw_start = (WIN_HEIGHT / 2 - (blazko->rays[q].wall_height / 2));
		blazko->rays[q].draw_start = (blazko->rays[q].draw_start < 0) ? 0 : blazko->rays[q].draw_start;
		blazko->rays[q].draw_end = (WIN_HEIGHT / 2 + (blazko->rays[q].wall_height / 2));
		blazko->rays[q].draw_end = (blazko->rays[q].draw_end > WIN_HEIGHT) ? WIN_HEIGHT : blazko->rays[q].draw_end;
		y = -1;
		if (blazko->rays[q].draw_start > 0)
			draw_ceiling(blazko, &(blazko->rays[q]), &y, q);
		draw_walls(blazko, &(blazko->rays[q]), &y, q);
		if (y < WIN_HEIGHT)
			draw_floor(blazko, &(blazko->rays[q]), &y, q);
	}
}

void	render_color_buf(t_wolf3d *blazko)
{
	SDL_UpdateTexture(blazko->color_tex, NULL,
		blazko->color_buffer, (int)(WIN_WIDTH * (sizeof(uint32_t))));
	SDL_RenderCopy(blazko->render, blazko->color_tex, NULL, NULL);
}

void	draw_ceiling(t_wolf3d *blazko, t_ray *this_ray, int *y, int x)
{
	uint32_t	color_step;
	uint32_t	color;
	uint32_t 	color_start;

	color_start = 0xFF440011;
	color = color_start;
	if (blazko->sound.is_m)
		color_step = (0xFFFFFFFF - color) / this_ray->draw_start;
	else
		color_step = 0x00010000;
	while (++(*y) < this_ray->draw_start)
	{
		if (color >=  0xFFFFFFFF || color < color_start)
			color_step = 0;	
		blazko->color_buffer[(WIN_WIDTH * (*y)) + x] = color;
		((*y) % 2 == 0) ? color += color_step : 0;
	}
	return ;
}

void	draw_floor(t_wolf3d *blazko, t_ray *this_ray, int *y, int x)
{
	uint32_t color_step;
	uint32_t color;
	uint32_t color_start;

	color_start = 0xFFFFFFFF;
	color = color_start;
	if (blazko->sound.is_m)
		color_step = (0x66778899 - color) / this_ray->draw_start;
	else
		color_step = 0x00010000;
	while (++(*y) < WIN_HEIGHT)
	{
		if (color <=  0 || color > color_start)
			color_step = 0;
		blazko->color_buffer[(WIN_WIDTH * (*y)) + x] = color;
		((*y) % 2 == 0) ? color -= color_step : 0;
	}
	return ;
}

void	draw_walls(t_wolf3d *blazko, t_ray *this_ray, int *y, int x)
{
	t_v2int	offset;
	uint32_t color_from_tex;
	float luminess;
	int		texture_index;

	*y = blazko->rays[x].draw_start - 1;
	if (blazko->rays[x].hit_is_vert)
		offset.x = ((int)blazko->rays[x].wall_hit.y) % TEXTURE_HEIGHT;
	else
		offset.x = ((int)blazko->rays[x].wall_hit.x) % TEXTURE_WIDTH;
	texture_index = (blazko->rays[x].hit_side);
	while (++(*y) < blazko->rays[x].draw_end)
	{
		luminess = (this_ray->distance / (float)TILE_SIZE) * 0.1f;
		offset.y = (*y + (blazko->rays[x].wall_height / 2) -
					(WIN_HEIGHT / 2)) * ((float)TEXTURE_HEIGHT
					/ blazko->rays[x].wall_height);
		color_from_tex = blazko->textures[texture_index]
					[(TEXTURE_WIDTH * offset.y) + offset.x];
		blazko->color_buffer[(WIN_WIDTH * (*y)) + x] =
		make_darkness(color_from_tex, luminess,
		blazko->rays[x].hit_is_vert, blazko->sound.is_m);
	}
	return ;
}

void	render(t_wolf3d *blazko)
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
