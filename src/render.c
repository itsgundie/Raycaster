
#include "../includes/wolf3d.h"

int		scale_column_to_draw(float tile_dimension, float distance)
{
	// if (distance <= 0.0f)
	// 	return ((int)((float)WIN_HEIGHT / tile_dimension) + 1);
	//float ska;
	//float to_z_projection_plane = (WIN_WIDTH / 2) / tan(FOV / 2);
	return((int)(fabs((tile_dimension / distance) * (float)TILE_SIZE))));
	// if (ska < 1.00f)
	// 	return((int)-(1.00f / ska));
	// if (ska > 1.00f)
	// 	return((int)ska);
	// else
	// 	return(1);
	//return (ska);
	//return((int)(((tile_dimension / distance) < 1.0f) ? (1.0f / (tile_dimension / distance)) : tile_dimension / distance));
}

void	get_surface_slice(t_ray	*this_ray, uint32_t *tex_column, SDL_Surface *this_surf)
{
	int			tex_column_index;
	t_v2_int	tex_coords = {0};
	uint32_t	q;
	int			bpp;
	uint8_t		*p;

	q = -1;
	bpp = this_surf->format->BytesPerPixel;
	p = (uint8_t*)tex_column;
	tex_column_index = ((this_ray->hit_is_hor == 1) ? (this_ray->pos.x) : (this_ray->pos.y));
	tex_column_index %= TILE_SIZE;
	while(++q < TILE_SIZE)
	{

		p = (uint8_t*)(this_surf->pixels + q * (this_surf->pitch) + tex_column_index * bpp);
		if (bpp == 1)
			*(tex_column + q) = (uint32_t)((*p));
		else if (bpp == 2)
			*(tex_column + q) = (uint32_t)(*((uint16_t*)p));
		else if (bpp == 3)
		{
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
				*(tex_column + q) = (uint32_t)(p[0] << 16 | p[1] << 8 | p[2]);
		
			else
				*(tex_column + q) = (uint32_t)(p[0] | p[1] << 8 | p[2] << 16);
		
		}
		else if (bpp == 4)
			*(tex_column + q) = (*((uint32_t*)p));
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
	
	
	q = 0;
	SDL_RenderClear(w->rend);
	while(q < WIN_WIDTH)
	{
	float scaler = scale_column_to_draw((float)TILE_SIZE, (float)w->ray[q].distance);
	get_surface_slice(&(w->ray[q]), tex_column, (w->surf[0][(w->ray[q].hit_index)]));
	color_index = ((uint8_t*)&(tex_column[0]));
	start_draw.x = q;
	start_draw.y = (WIN_HEIGHT / 2 - scaler / 2);
	(start_draw.y < 0) ? (start_draw.y = 0) : 0;
	// tex_draw_index += ((int)(scaler * (float)TILE_SIZE)) / 2;
	tex_draw_index = TILE_SIZE / 2;
	while(start_draw.y < WIN_HEIGHT && tex_draw_index < 128)
	{
		scaler_loop	= 0;
		if (scaler > TILE_SIZE)
		{
			int z = scaler / TILE_SIZE;
			scaler_loop = z;
			while(z > 0)
			{
				SDL_SetRenderDrawColor(w->rend, color_index[tex_draw_index * 4], color_index[tex_draw_index * 4 + 1], 
										color_index[tex_draw_index * 4 + 2] , color_index[tex_draw_index * 4 + 3]);
				SDL_RenderDrawPoint(w->rend, start_draw.x, (start_draw.y + scaler_loop));
				z--;
			}
		}






		
		
		if (scaler < 1.00f)
		{

		}

		while (scaler_loop < (int)scaler)
		{
		// 	SDL_SetRenderDrawColor(w->rend, 44, 
		// 								144 , 244, 255);
			
			scaler_loop++;
		}
		start_draw.y = start_draw.y + scaler_loop;
		tex_draw_index++;
	}
	q++;
	}
	SDL_RenderPresent(w->rend);	
	return ;
}



