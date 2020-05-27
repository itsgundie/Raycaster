#include "../includes/wolf3d.h"

void	draw_ceiling(t_wolf3d *blazko, t_ray *this_ray, int *y, int x)
{
	uint32_t color_step;
	uint32_t color;
	t_argb	 grad = {0};
	uint32_t color_start;

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
}

void	draw_floor(t_wolf3d *blazko, t_ray *this_ray, int *y, int x)
{
	uint32_t color_step;
	uint32_t color;
	t_argb	 grad = {0};
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
	while(++(*y) < blazko->rays[x].draw_end)
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
}
