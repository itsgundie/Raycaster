#include "../includes/wolf3d.h"

void texture_manager(t_wolf3d *blazko)
{
	int q;

	q= -1;
	if (!(blazko->color_buffer = (uint32_t*)malloc(sizeof(uint32_t) 
			* (uint32_t)WIN_WIDTH * (uint32_t)WIN_HEIGHT)))
		error_exit("Malloc of color_buff Not OK -_-\n", blazko);
	if (!(blazko->color_tex = SDL_CreateTexture(blazko->render,
				SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
		 		WIN_WIDTH, WIN_HEIGHT)))
		error_exit("Malloc of color_tex Not OK -_-\n", blazko);
	blazko->surfs_for_texes[0] = IMG_Load(TEXTURE_0);
	blazko->surfs_for_texes[1] = IMG_Load(TEXTURE_1);
	blazko->surfs_for_texes[2] = IMG_Load(TEXTURE_2);
	blazko->surfs_for_texes[3] = IMG_Load(TEXTURE_3);
	blazko->surfs_for_texes[4] = IMG_Load(TEXTURE_4);
	while(blazko->surfs_for_texes[++q]);
	if (q < NUM_OF_TEXTURES)
		error_exit("Malloc Not OK, particularly loading textures", blazko);
	q = -1;
	while (++q < NUM_OF_TEXTURES)
		blazko->textures[q] = (uint32_t*)(blazko->surfs_for_texes[q]->pixels);
}

void	make_a_move(t_wolf3d *blazko, float delta_time)
{
	float move_step;
	t_v2	new_pos;

	printf( "player angle before move is %f\n",blazko->player.rotation_angle);
	printf( "player before move x - %f and y - %f\n", blazko->player.pos.x, blazko->player.pos.y);
	blazko->player.rotation_angle += (((blazko->player.turn_direction)
			* (blazko->player.rotate_speed))); //* delta_time);
	blazko->player.rotation_angle = normalize_angle(blazko->player.rotation_angle);
	move_step = blazko->player.walk_direction * blazko->player.move_speed; //* delta_time;
	new_pos.x = (blazko->player.pos.x + cos(blazko->player.rotation_angle) * move_step);
	new_pos.y = (blazko->player.pos.y + sin(blazko->player.rotation_angle) * move_step);
	printf("this is a move_step - %f\n", move_step);
	printf("this is a new_pos.x - %f\n", new_pos.x);
	printf("this is a new_pos.y - %f\n", new_pos.y);
	if (!(find_an_obstacle(floor(new_pos.x) ,floor(new_pos.y), &(blazko->map))))
	{
		blazko->player.pos.x = new_pos.x;
		blazko->player.pos.y = new_pos.y;
	}
	printf( "player angle after move is %f\n",blazko->player.rotation_angle);
	printf( "player after move x - %f and y - %f\n", blazko->player.pos.x, blazko->player.pos.y);
}

float	normalize_angle(float angle)
{
	float norm_angle;
	norm_angle = angle;
	if (norm_angle > TWO_PI)
		norm_angle = remainderf(angle, TWO_PI);
	if (norm_angle < 0)
		norm_angle = TWO_PI + norm_angle;
	return(norm_angle);
}

float calc_distance(float x1, float y1, float x2, float y2)
{
	return(sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

int	is_looking_down(float angle)
{
	return(angle >= 0 && angle <= PI);
}

int	is_looking_right(float angle)
{
	return((angle <= (0.5 * PI)) || (angle >= (1.5 * PI)));
}

void	update(t_wolf3d *blazko, long long *ticks_last_frame)
{
	int time_to_wait;
	time_to_wait = blazko->frame_time - (SDL_GetTicks() - *ticks_last_frame);

	if (time_to_wait > 0 && time_to_wait <= blazko->frame_time)
		SDL_Delay(time_to_wait);

	while(!(SDL_TICKS_PASSED(SDL_GetTicks(), (*ticks_last_frame + blazko->frame_time))));

	float delta_time = (SDL_GetTicks() - *ticks_last_frame) * 1000.0f;
	*ticks_last_frame = SDL_GetTicks();
	make_a_move(blazko, delta_time); //?
	raycast(blazko); //?
}

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
					blazko->rays[x].hit_is_vert, blazko->sound.is_m);			//(blazko->rays[q].hit_is_vert ? 0xFFFFFFFF : 0xFFBBCCDD);
		}
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

void	clear_color_buf(uint32_t *color_buf, uint32_t color)
{
	int x;
	int y;

	x = -1;
	while (++x < WIN_WIDTH)
	{
		y = -1;
		while (++y < WIN_HEIGHT)
			color_buf[(WIN_WIDTH * y) + x] = color;
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

int		main(int argc, char **argv)
{
	t_wolf3d *blazko;
	int fd;
	long long ticks_last_frame;

	if (argc != 2 || (fd = open(argv[1], O_RDONLY)) < 0)
		ft_error("usage: ./wolf3d map");
	ticks_last_frame = SDL_GetTicks();
	if (!(blazko = init()))
		return (1);
	if (file_parser(blazko, fd))
		create_map(blazko);
	setup(blazko);
	music_on(blazko);
	int i = 0;
	int i2 = 0;
	while (i < blazko->map.rows)
	{
		i2 = 0;
		while (i2 < blazko->map.columns)
		{
			ft_printf("%d ", blazko->map.map[i][i2]);
			i2++;
		}
		ft_printf("\n");
		i++;
	}
	while(1)
	{
		if (!(put_in(blazko)))
			break ;
		update(blazko, &ticks_last_frame);
		make_a_move(blazko, ticks_last_frame);
		render(blazko);
	}
	destroy(blazko);
	return(0);
}