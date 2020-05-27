#include "../includes/wolf3d.h"

uint32_t		make_darkness(uint32_t color, float intensity, int is_vertical, int disco)
{
	t_argb palet;
	uint32_t disco_move;
	if (disco)
	{
		intensity = 1.0f - intensity;
		is_vertical ? intensity -= 0.1 : intensity;
		palet.a = ((color >> 24) & 0xFF);
		palet.r = (((color >> 16) & 0xFF) / intensity * 2);
		palet.g = (((color >> 8) & 0xFF) / intensity * 0.5f);
		palet.b = ((color & 0xFF) / intensity * 0.33f);
		return((palet.a << 24) | (palet.r << 16) | (palet.g << 8) | palet.b);	
	}
	if (color == 0)
		return(0);
	if (intensity > 0.9f)
		return(0);
	if (intensity <= 0.0f)
		return(color);
	intensity = 1.0f - intensity;
	is_vertical ? intensity -= 0.1 : intensity;
	palet.a = ((color >> 24) & 0xFF);
	palet.r = (((color >> 16) & 0xFF) * intensity);
	palet.g = (((color >> 8) & 0xFF) * intensity);
	palet.b = ((color & 0xFF) * intensity);
	return((palet.a << 24) | (palet.r << 16) | (palet.g << 8) | palet.b);
}

void	make3d(t_wolf3d *blazko)
{
	int q;
	int y;
	float dist_to_proj_plane;
	float perpendicular_dist;
	
	q = -1;
	dist_to_proj_plane = (WIN_WIDTH / 2) / tan(blazko->player.fov / 2);
	while (++q < RAYS_NUM)
	{
		perpendicular_dist	= blazko->rays[q].distance * cos(blazko->rays[q].angle - blazko->player.rotation_angle);
		blazko->rays[q].wall_height = (int)((TILE_SIZE / perpendicular_dist) * dist_to_proj_plane);
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

void	render(t_wolf3d *blazko)
{
	SDL_SetRenderDrawColor(blazko->render, 0, 0, 0 , 255);
	SDL_RenderClear(blazko->render);
	make3d(blazko);
	render_map(blazko);
	render_rays(blazko);
	render_color_buf(blazko);
	clear_color_buf(blazko->color_buffer, 0xFF333333);
	SDL_RenderPresent(blazko->render);
	stop_step(blazko);
}
