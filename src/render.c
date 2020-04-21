
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

void	render_it(t_wolfec *w)
{
	while(this_ray[q] < WIDTH)
	{
	int scaler = get_scaler_for_drawing_column((float)TILE_SIZE / (float)this_ray->distance);
	get_texture_slice(&(this_ray->hit_index), &(this_ray->pos));
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



