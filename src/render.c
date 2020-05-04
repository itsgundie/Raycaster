
#include "../includes/wolf3d.h"

int		scale_column_to_draw(float tile_dimension, float distance)
{
	// if (distance <= 0.0f)
	// 	return ((int)((float)WIN_HEIGHT / tile_dimension) + 1);
	//float ska;
	int rez;
	int max;
	//distance = (WIN_HEIGHT > distance ? distance : WIN_HEIGHT);
	float to_z_projection_plane;
	to_z_projection_plane = (((float)WIN_WIDTH / 2) / tan(degrees_to_rads((float)(FOV / 2))));
	rez = ((int)(fabs((((tile_dimension / distance) * tile_dimension))))); // tile_dimension))); //));
	return((rez)); //>> 1) << 1);
	//max = ((int)(fabs((((tile_dimension / WIN_HEIGHT) * tile_dimension)))));;
	//return((rez < max) ? rez : max);
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


void	put_pixel_to_render(SDL_Renderer *rend, uint8_t *color, t_v2_int *coords)
{
	SDL_SetRenderDrawColor(rend, *color, *(color + 1), *(color + 2), *(color + 3));
	SDL_RenderDrawPoint(rend, coords->x, coords->y);
	return ;
}



// void	draw_shrinked_line(t_wolfec *w, uint8_t *color_index, t_v2_float *start_draw, int *scaler)
// {
// 	float step_y = ((float)*scaler / (float)TILE_SIZE);
// 	float index = step_y;
// 	int draw_length = *scaler;
// 	start_draw->y = WIN_HEIGHT / 2 - *scaler / 2;
// 	while (draw_length > 0 || start_draw->y < WIN_HEIGHT)
// 	{
// 		put_pixel_to_render(&(w->rend), &(color_index[(((int)index) * 4)]), &start_draw);
// 		index += step_y;
// 		draw_length--;
// 		(start_draw->y)++;
// 	}
// 	return ;
// }


// void	draw_stretched_line(t_wolfec *w, uint8_t *color_index, t_v2_float *start_draw, int *scaler)
// {
	
// 	int	scale = *scaler / TILE_SIZE;
// 	float index = 0;
// 	int draw_length = *scaler;
// 	int loop = 0;
// 	//start_draw->y = WIN_HEIGHT / 2 - *scaler / 2;
// 	//start_draw->y < 0 ? start_draw->y = 0 : 0; 
// 	if (*scaler > WIN_HEIGHT)
// 		color_index = color_index + 4 * ( TILE_SIZE - 1 
// 			- ((int)((float)WIN_HEIGHT / (float)(*scaler) * (float)TILE_SIZE) / 2));
// 	while (draw_length > 0 || start_draw->y < WIN_HEIGHT)
// 	{
// 		loop = 1
// 		while (loop < scale)
// 		{
// 			put_pixel_to_render(&(w->rend), &(color_index[(((int)index) * 4 + loop)]), &start_draw);
// 			loop++
// 		}
// 		put_pixel_to_render(&(w->rend), &(color_index[(((int)index) * 4 + loop)]), &start_draw);
// 		index += step_y;
// 		draw_length--;
// 		(start_draw->y)++;
// 	}
// 	return ;
// }

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
	//SDL_SetRenderDrawColor(w->rend, 0, 0, 0, 255);
	//SDL_RenderClear(w->rend);
	while(q < WIN_WIDTH)
	{
		// if ((q % 10) == 0)
		// 	write(1, "breakpont\n", 10);
		if (q > 630)
			write(1, "\n", 1);
	int col_height = scale_column_to_draw((float)TILE_SIZE, w->ray[q].distance);
	get_surface_slice(&(w->ray[q]), tex_column, (w->surf[0][(w->ray[q].hit_index) + 1]));
	color_index = ((uint8_t*)&(tex_column[0]));
	start_draw.x = q;
	start_draw.y = (WIN_HEIGHT / 2 - col_height / 2);
	(start_draw.y < 0) ? (start_draw.y = 0) : start_draw.y;
	int	scale = col_height / TILE_SIZE;
	float index = 0;
	int draw_length = ((col_height < WIN_HEIGHT) ? col_height : WIN_HEIGHT);
	int loop = 0;
	float step_y = (((float)col_height / (float)TILE_SIZE) - (float)((int)((float)col_height / (float)TILE_SIZE)));
	// if (col_height > WIN_HEIGHT)
	// {
	// 	index = (float)( TILE_SIZE - 1 - ((int)((float)WIN_HEIGHT / (float)(col_height) * (float)TILE_SIZE) / 2));
	// 		// color_index = color_index + 4 * ( TILE_SIZE - 1 
	// 		// - ((int)((float)WIN_HEIGHT / (float)(scaler) * (float)TILE_SIZE) / 2));
	// }
	uint32_t *color_ptr;
	uint32_t color = 0x88888888;
	color_ptr = &color;
	color_index = ((uint8_t*)color_ptr);
	while ((draw_length > 0) && (start_draw.y < WIN_HEIGHT))
	{
		// loop = 0;
		// while (loop < (scale) && (scale > 1))
		// {
		// 	put_pixel_to_render((w->rend), &(color_index[0]), &start_draw);
		// 	start_draw.y++;
		// 	loop++;
		// 	draw_length--;
		// }
		if ((draw_length > 0) && (start_draw.y < WIN_HEIGHT))
		{
			put_pixel_to_render((w->rend), &(color_index[0]), &start_draw);
			draw_length--;
			(start_draw.y)++;
		}
// 		while ((loop < (scale) && (scale > 1) && (draw_length > 0)))//&& (scale > 1))
// 		{
// 			put_pixel_to_render((w->rend), &(color_index[((int)index) * 4]), &start_draw);
// 			start_draw.y++;
// 			loop++;
// 			draw_length--;
// 		}
// 		if ((draw_length > 0) && (((int)index) < TILE_SIZE))
// 		{
// 			put_pixel_to_render((w->rend), &(color_index[(((int)index) * 4)]), &start_draw);
// 			index = step_y;
// 			draw_length--;
// 			(start_draw.y)++;
// 		}
	} 
	q++;
	}
	SDL_RenderPresent(w->rend);	
	return ;
}






	
	
	// tex_draw_index = 0; //TILE_SIZE / 2;
	// float step_y = ((float)*scaler / (float)TILE_SIZE);
	// float index = step_y;
	// int draw_length = scaler;
	// scale = scaler / TILE_SIZE;
	// scaler_loop = 0;
	// if (scaler < TILE_SIZE)
	// 	draw_shrinked_line(w, color_index, &start_draw, &scaler);
	// else if (scaler < TILE_SIZE)
	// 	draw_stretched_line(w, color_index, &start_draw, &scaler);
	
	// while (draw_length > 0)
	// {
	// 	put_pixel_to_render(&(w->rend), &(color_index[(((int)index) * 4)]), &start_draw);
	// 	index += step_y;
	// 	draw_length--;
	// 	(start_draw->y)++;
	// }
	// }




	// while(start_draw.y < WIN_HEIGHT && tex_draw_index < 128)
	// {
	// 	scaler_loop	= 0;
	// 	if (scaler > TILE_SIZE)
	// 	{
	// 		int z = scaler / TILE_SIZE;
	// 		scaler_loop = z;
	// 		while(z > 0)
	// 		{
	// 			SDL_SetRenderDrawColor(w->rend, color_index[tex_draw_index * 4], color_index[tex_draw_index * 4 + 1], 
	// 									color_index[tex_draw_index * 4 + 2] , color_index[tex_draw_index * 4 + 3]);
	// 			SDL_RenderDrawPoint(w->rend, start_draw.x, (start_draw.y + scaler_loop));
	// 			z--;
	// 		}
	// 	}
	// 	if (scaler < 1.00f)
	// 	{

	// 	}

	// 	while (scaler_loop < (int)scaler)
	// 	{
	// 	// 	SDL_SetRenderDrawColor(w->rend, 44, 
	// 	// 								144 , 244, 255);
			
	// 		scaler_loop++;
	// 	}
	// 	start_draw.y = start_draw.y + scaler_loop;
	// 	tex_draw_index++;