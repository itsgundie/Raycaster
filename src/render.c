
#include "../includes/wolf3d.h"

// void	get_rect(SDL_Rect *source, SDL_Rect *destin)
// {
// 	source->h = 128;
// 	source->w = 128;
// 	source->x = 0;
// 	source->y = 0;

// 	destin->w = 128;
// 	destin->h = 128; //distance
// 	destin->x = 0; // ray num
// 	destin->y = 0;  // cent.y -  (destin.h / 2) 
// }

int		get_scaler_for_drawing_column(float tile_dimension, float distance)
{
	return((int)((tile_dimension / distance) < 1.0f ? 1.0f : tile_dimension / distance));
}

void	get_surface_slice(t_ray	*this_ray, uint32_t *tex_column, SDL_Surface *this_surf)
{
	int			tex_column_index;
	t_v2_int	tex_coords = {0};
	uint32_t	q;

	q = -1;
	tex_column_index = ((this_ray->hit_index == 1) ? (this_ray->pos.x) : (this_ray->pos.y));
	tex_column_index %= TILE_SIZE;
	while(++q < TILE_SIZE)
	{
		tex_column[q] = (Uint32*)this_surf->pixels + q * this_surf->pitch + tex_column_index; 
	}
	return ;
}

void	render_it(t_wolfec *w)
{
	int			q;
	uint32_t	tex_column[TILE_SIZE] = {0};

	q = 0;
	while(w->ray[q] < WIDTH)
	{
	int scaler = get_scaler_for_drawing_column((float)TILE_SIZE / (float)this_ray->distance);
	get_texture_slice(&(w->ray[q]), tex_column, &(w->surf[0][(w->ray[q].hit_index)]));
	SDL_SetRenderDrawColor
	
	draw_scaled_column(tex_buffer, ray[index])
	}




	// SDL_RenderClear(rend);
	// SDL_Rect	source;
	// SDL_Rect	destin;
	// get_rect(&source, &destin,);
	// cycled_original(rend, tex, &source, &destin);
	// SDL_RenderPresent(rend);
	// SDL_Delay(3000);

	SDL_RenderCopy(w->rend, w->back, NULL, NULL);
	SDL_RenderPresent(w->rend);
}



