
#include "../includes/wolf3d.h"

int		get_scaler_for_drawing_column(float tile_dimension, float distance)
{
	return((int)((tile_dimension / distance) < 1.0f ? (1.0f / (tile_dimension / distance)) : tile_dimension / distance));
}

void	get_surface_slice(t_ray	*this_ray, uint32_t *tex_column, SDL_Surface *this_surf)
{
	int			tex_column_index;
	t_v2_int	tex_coords = {0};
	uint32_t	q;

	q = -1;
	tex_column_index = ((this_ray->hit_is_hor == 1) ? (this_ray->pos.x) : (this_ray->pos.y));
	tex_column_index %= TILE_SIZE;
	while(++q < TILE_SIZE)
	{
		tex_column[q] = (Uint32*)(this_surf->pixels) + q * ((this_surf->pitch) / 4) + tex_column_index; 
	}
	return ;
}

void	render_it(t_wolfec *w)
{
	int			q;
	int			h;
	int			tex_draw_index;
	int			scaler_loop;
	t_v2_int	start_draw = {0};
	uint32_t	tex_column[TILE_SIZE] = {0};
	uint8_t		*color_index;
	
	tex_draw_index = 0;
	q = 0;
	while(w->ray[q] < WIDTH)
	{
	int scaler = get_scaler_for_drawing_column((float)TILE_SIZE / (float)this_ray->distance);
	get_texture_slice(&(w->ray[q]), tex_column, &(w->surf[0][(w->ray[q].hit_index)]));
	color_index = (uint8_t)tex_column;
	start_draw.x = q;
	start_draw.y = ((WIN_HEIGHT / 2) - (scaler * (TILE_SIZE / 2)));
	(start_draw.y < 0) ? (start_draw.y = 0) : 0;
	tex_draw_index += (scaler * TILE_SIZE) / 2;
	while(start_draw.y < WIN_HEIGHT)
	{
		scaler_loop	= 0;
		while (scaler_loop < scaler)
		{
			
			SDL_SetRenderDrawColor(w->rend, color_index[tex_draw_index * 4], color_index[tex_draw_index * 4 + 1], 
										color_index[tex_draw_index * 4 + 2] , color_index[tex_draw_index * 4 + 4]);
			SDL_RenderDrawPoint(w->rend, start_draw.x, (start_draw.y + scaler_loop));
			scaler_loop++;
		}
		start_draw.y += scaler_loop;
		tex_draw_index++;
	}	
	}
	SDL_RenderPresent(w->rend);
	return ;
}



