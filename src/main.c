
#include <../includes/wolf3d.h>


void	destroy(t_wolf3d *blazko)
{
	int q;

	q = NUM_OF_TEXTURES;
	free(blazko->color_buffer);
	blazko->color_buffer = NULL;
	while (--q >= 0)
	{
		SDL_FreeSurface(blazko->surfs_for_texes[q]);
		blazko->surfs_for_texes[q] = NULL;
		blazko->textures[q] = NULL;
	}
	SDL_DestroyTexture(blazko->color_tex);
	SDL_DestroyRenderer(blazko->render);
	SDL_DestroyWindow(blazko->window);
	SDL_Quit();
}


int		init(t_wolf3d *blazko)
{
	blazko->window = NULL;
	blazko->render = NULL;
	blazko->wall_texture = NULL;
	blazko->color_buffer = NULL;
	blazko->color_tex = NULL;
	blazko->sound.badmusic = NULL;
	blazko->sound.is_m = 0;
	if (!(blazko->params_vars.params_list = (t_pars_list *)malloc(sizeof(t_pars_list))))
		printf("Malloc failed\n");
	blazko->params_vars.tmp = blazko->params_vars.params_list;
	blazko->params_vars.params_list->line = NULL;

	if ((SDL_Init(SDL_INIT_EVERYTHING)))
	{
		printf("Error Initializing SDL\n");
		return(FALSE);
	}
	if (!(blazko->window = SDL_CreateWindow(WIN_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, 0)))
	{
		printf("Error creating SDL window\n");
		return(FALSE);
	}
	if (!(blazko->render = SDL_CreateRenderer(blazko->window, -1, 0)))
	{
		printf("Error creating SDL render\n");
		return(FALSE);
	}
	//SDL_SetRenderDrawBlendMode(blazko->render, SDL_BLENDMODE_MOD);
	return(TRUE);
}


int		error_exit(char *str, t_wolf3d *blazko)
{
	printf("%s", str);
	destroy(blazko);
	exit(1);
}

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

void	setup(t_wolf3d *blazko)
{
	blazko->color_buffer = NULL;
	blazko->color_tex = NULL;
	texture_manager(blazko);
	blazko->player.width = 1;
	blazko->player.height = 1;
	blazko->player.turn_direction = 0;
	blazko->player.walk_direction = 0;
	blazko->player.rotation_angle = PI * 2.0f;
	blazko->player.fov = (FOV * (PI / 180));
	blazko->player.move_speed = 5;
	blazko->player.rotate_speed = 5 * (PI / 180);
	blazko->frame_time = 1000 / FPS;
	blazko->map.columns = blazko->params_vars.line_width + 2;
	blazko->map.rows = blazko->params_vars.number_of_lines + 2;
}

int		find_an_obstacle(float x, float y, t_2dmap *kapta)
{
	t_v2int check;

	if (x <= 0 || x >= (kapta->columns * TILE_SIZE)
		|| y <= 0 || y >= (kapta->rows * TILE_SIZE))
		return (TRUE);
	check.x = (int)(x / TILE_SIZE);
	check.y = (int)(y / TILE_SIZE);
	return(kapta->map[check.y][check.x] == 1);
}

void	make_a_move(t_wolf3d *blazko, float delta_time)
{
	float move_step;
	t_v2	new_pos;

	blazko->player.rotation_angle += ((blazko->player.turn_direction)
			* (blazko->player.rotate_speed)); //* delta_time);
	move_step = blazko->player.walk_direction * blazko->player.move_speed; //* delta_time;
	new_pos.x = blazko->player.pos.x + cos(blazko->player.rotation_angle) * move_step;
	new_pos.y = blazko->player.pos.y + sin(blazko->player.rotation_angle) * move_step;
	if (!find_an_obstacle(new_pos.x ,new_pos.y, &(blazko->map)))
	{
		blazko->player.pos.x = new_pos.x;
		blazko->player.pos.y = new_pos.y;
	}
}

float	normalize_angle(float angle)
{
	float norm_angle;
	norm_angle = remainderf(angle, TWO_PI);
	if (norm_angle < 0)
		norm_angle = TWO_PI + norm_angle;
	return(norm_angle);
}

float calc_distance(float x1, float y1, float x2, float y2)
{
	return(sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	find_wall_side(t_ray *this_ray, t_2dmap *kapta)
{
	t_v2int pos;

	
	pos.x = (int)(this_ray->wall_hit.x / (float)TILE_SIZE);
	pos.y = (int)(this_ray->wall_hit.y / (float)TILE_SIZE);

	if (pos.x == 0 || pos.x == (kapta->columns - 1) || pos.y == 0 || pos.y == (kapta->rows - 1))
		this_ray->hit_side = 4;
	else if (this_ray->hit_side)
	{
		if (this_ray->hit_is_vert)
		{
			if (this_ray->ray_is_up && this_ray->ray_is_left)
				this_ray->hit_side = 1;
			else if (this_ray->ray_is_down && this_ray->ray_is_left)
				this_ray->hit_side = 1;
			else if (this_ray->ray_is_up && this_ray->ray_is_right)
				this_ray->hit_side = 3;
			else if (this_ray->ray_is_down && this_ray->ray_is_right)
				this_ray->hit_side = 3;
		}
		else
		{
			if (this_ray->ray_is_up && this_ray->ray_is_left)
				this_ray->hit_side = 2;
			else if (this_ray->ray_is_up && this_ray->ray_is_right)
				this_ray->hit_side = 2;
			else if (this_ray->ray_is_down && this_ray->ray_is_right)
				this_ray->hit_side = 0;
			else if (this_ray->ray_is_down && this_ray->ray_is_left)
				this_ray->hit_side = 0;
		}	
	}
	return ;
}

void	horz_intersect(t_wolf3d *blazko, t_ray *this_ray)
{
	t_v2 intercept_hor;
	t_v2 step_hor;
	t_v2 next_hor;
	t_v2 check_hor;

	intercept_hor.y = floor(blazko->player.pos.y / TILE_SIZE) * TILE_SIZE;
	intercept_hor.y += (this_ray->ray_is_down) ? TILE_SIZE : 0;

	intercept_hor.x = blazko->player.pos.x + 
		(intercept_hor.y - blazko->player.pos.y) / tan(this_ray->angle);

	step_hor.y = ((this_ray->ray_is_up) ? -1 : 1) * TILE_SIZE;
	step_hor.x = TILE_SIZE / tan(this_ray->angle);
	step_hor.x *= (this_ray->ray_is_left && step_hor.x > 0) ? -1 : 1;
	step_hor.x *= (this_ray->ray_is_right && step_hor.x < 0) ? -1 : 1;

	next_hor.x = intercept_hor.x;
	next_hor.y = intercept_hor.y;

	while (next_hor.x >= 0 && next_hor.x <= (blazko->map.columns * TILE_SIZE)
			&& next_hor.y >= 0 && next_hor.y <= (blazko->map.rows * TILE_SIZE))
	{
		check_hor.x = next_hor.x;
		check_hor.y = next_hor.y + (this_ray->ray_is_up ? -1 : 0);

		if (find_an_obstacle(check_hor.x, check_hor.y, &(blazko->map)))
		{
			this_ray->wall_hit.x = next_hor.x;
			this_ray->wall_hit.y = next_hor.y;

			this_ray->hit_side = (blazko->map.map[(int)floor(check_hor.y / TILE_SIZE)]
								[(int)floor(check_hor.x / TILE_SIZE)]);
			this_ray->hit_is_horz = TRUE;
			break;
		}
		else
		{
			next_hor.x += step_hor.x;
			next_hor.y += step_hor.y;
		}
	}	
}

void	vert_intersect(t_wolf3d *blazko, t_ray *this_ray)
{
	t_v2 intercept_ver;
	t_v2 step_ver;
	t_v2 next_ver;
	t_v2 check_ver;

	intercept_ver.x = floor(blazko->player.pos.x / TILE_SIZE) * TILE_SIZE;
	intercept_ver.x += (this_ray->ray_is_right ? TILE_SIZE : 0);
	intercept_ver.y = blazko->player.pos.y + (intercept_ver.x - blazko->player.pos.x) * tan(this_ray->angle);
	step_ver.x = TILE_SIZE;
	step_ver.x *= (this_ray->ray_is_left ? -1 : 1);
	step_ver.y = TILE_SIZE * tan(this_ray->angle);
	step_ver.y *= (this_ray->ray_is_up && step_ver.y > 0) ? -1 : 1;
	step_ver.y *= (this_ray->ray_is_down && step_ver.y < 0) ? -1 : 1;
	next_ver.x = intercept_ver.x;
	next_ver.y = intercept_ver.y;
	while (next_ver.x >= 0 && next_ver.x <= (blazko->map.columns * TILE_SIZE) 
		&& next_ver.y >= 0 && next_ver.y <= (blazko->map.rows * TILE_SIZE))
	{
		check_ver.x = next_ver.x + (this_ray->ray_is_left ? -1 : 0);
		check_ver.y = next_ver.y;
		if (find_an_obstacle(check_ver.x, check_ver.y, &(blazko->map)))
		{
			 this_ray->wall_hit.x = next_ver.x;
			 this_ray->wall_hit.y = next_ver.y;
			 this_ray->hit_side = blazko->map.map[(int)floor(check_ver.y / TILE_SIZE)][(int)floor(check_ver.x / TILE_SIZE)];
			 this_ray->hit_is_vert = TRUE;
			 break;
		}
		else
		{
			next_ver.x += step_ver.x;
			next_ver.y += step_ver.y;
		}
	}

}

void	cast_this_ray(t_wolf3d *blazko, t_ray *this_ray)
{
	t_ray	save_horz_data = {0};

	horz_intersect(blazko, this_ray);
	save_horz_data = *this_ray;
	vert_intersect(blazko, this_ray);
	float distance_hor = (save_horz_data.hit_is_horz ? 
		calc_distance(blazko->player.pos.x, blazko->player.pos.y,
		 save_horz_data.wall_hit.x, save_horz_data.wall_hit.y) : INT_MAX);
	float distance_ver = (this_ray->hit_is_vert ? 
		calc_distance(blazko->player.pos.x, blazko->player.pos.y,
			this_ray->wall_hit.x, this_ray->wall_hit.y) : INT_MAX);
	if (distance_ver < distance_hor)
	{
		this_ray->distance = (distance_ver <= 0 ? 1 : distance_ver);
		this_ray->hit_is_horz = FALSE;
	}
	else
	{
		*this_ray = save_horz_data;
		this_ray->distance = (distance_hor <= 0 ? 1 : distance_hor);
		this_ray->hit_is_vert = FALSE;
	}
	find_wall_side(this_ray, &(blazko->map));
}

int	is_looking_down(float angle)
{
	return(angle > 0 && angle < PI);
}

int	is_looking_right(float angle)
{
	return((angle < (0.5 * PI)) || (angle > (1.5 * PI)));
}

void	raycast(t_wolf3d *blazko)
{
	int q;

	q = -1;
	float ray_angle = blazko->player.rotation_angle - (blazko->player.fov / 2);
	while (++q < WIN_WIDTH)
	{
		blazko->rays[q].angle = normalize_angle(ray_angle);
		blazko->rays[q].ray_is_down = is_looking_down(blazko->rays[q].angle);
		blazko->rays[q].ray_is_right = is_looking_right(blazko->rays[q].angle);
		blazko->rays[q].ray_is_up = !(blazko->rays[q].ray_is_down);
		blazko->rays[q].ray_is_left = !(blazko->rays[q].ray_is_right);
		cast_this_ray(blazko, &(blazko->rays[q]));
		ray_angle += (blazko->player.fov / WIN_WIDTH);
	}
}

void	render_player(t_wolf3d *blazko)                                 //need refactor breizenheima
{
	SDL_SetRenderDrawColor(blazko->render, 255, 255, 255, 255);
	SDL_Rect player_rect = {blazko->player.pos.x * MINIMAP_SCALE,
							blazko->player.pos.y * MINIMAP_SCALE,
							blazko->player.width * MINIMAP_SCALE,
							blazko->player.height * MINIMAP_SCALE};
	SDL_RenderFillRect(blazko->render, &player_rect);
	SDL_RenderDrawLine(blazko->render, blazko->player.pos.x * MINIMAP_SCALE,
						blazko->player.pos.y * MINIMAP_SCALE,
						blazko->player.pos.x * MINIMAP_SCALE + cos(blazko->player.rotation_angle) * 40,
						blazko->player.pos.y * MINIMAP_SCALE + sin (blazko->player.rotation_angle) * 40);
}

void	render_map(t_wolf3d *blazko)           							//need refactor
{
	int j;
	int k;

	j = 0;
	k = 0;

	while (j < blazko->map.rows)
	{
		k = 0;
		while (k < blazko->map.columns)
		{
			int tile_x = (k * TILE_SIZE);
			int tile_y = (j * TILE_SIZE);
			int tile_color = blazko->map.map[j][k] == 1 ? 255 : 0;
			SDL_SetRenderDrawColor(blazko->render, tile_color, tile_color, tile_color, 255);
			SDL_Rect map_tile_rect = {tile_x * MINIMAP_SCALE, tile_y * MINIMAP_SCALE,
										 TILE_SIZE * MINIMAP_SCALE, TILE_SIZE * MINIMAP_SCALE};
			SDL_RenderFillRect(blazko->render, &map_tile_rect);
			k++;
		}
		j++;
	}
}

void	render_rays(t_wolf3d *blazko)
{
	int q;

	q = -1;
	SDL_SetRenderDrawColor(blazko->render, 255, 0, 0, 255);
	while (++q < WIN_WIDTH)
	{
		SDL_RenderDrawLine(blazko->render,
							blazko->player.pos.x * MINIMAP_SCALE,
							blazko->player.pos.y * MINIMAP_SCALE,
							blazko->rays[q].wall_hit.x * MINIMAP_SCALE,
							blazko->rays[q].wall_hit.y * MINIMAP_SCALE);
	}
}

void	play_step(t_wolf3d *blazko)
{
	if (!Mix_Playing(2))
		Mix_PlayChannel(2, blazko->sound.step, 0);	
}

void	stop_step(t_wolf3d *blazko)
{
	if (blazko->player.walk_direction == 0 
	&& blazko->player.walk_direction == 0
	&& blazko->player.turn_direction == 0
	&& blazko->player.turn_direction == 0)
	Mix_HaltChannel(2);
}

void	input(int *game_on, t_wolf3d *blazko)
{
	SDL_Event event;
	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT)
	{
		*game_on = FALSE;
	}
	else if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_m)
		{
			if (blazko->sound.is_m == 0)
			{
				blazko->sound.is_m = 1;
				Mix_PlayMusic(blazko->sound.badmusic, 15);
			}
			else
			{
				blazko->sound.is_m = 0;
				Mix_FadeOutMusic(500);
			}
		}
		if (event.key.keysym.sym == SDLK_ESCAPE)
			*game_on = FALSE;
		if (event.key.keysym.sym == SDLK_UP)
		{
			blazko->player.walk_direction = +1;
			play_step(blazko);
		}
		if (event.key.keysym.sym == SDLK_DOWN)
		{
			blazko->player.walk_direction = -1;
			play_step(blazko);
		}
		if (event.key.keysym.sym == SDLK_RIGHT)
		{
			blazko->player.turn_direction = +1;
			play_step(blazko);
		}
		if (event.key.keysym.sym == SDLK_LEFT)
		{
			blazko->player.turn_direction = -1;
			play_step(blazko);
		}
	}
	else if (event.type == SDL_KEYUP)
	{
		if (event.key.keysym.sym == SDLK_UP)
		{
			blazko->player.walk_direction = 0;
			stop_step(blazko);
		}
		if (event.key.keysym.sym == SDLK_DOWN)
		{
			blazko->player.walk_direction = 0;
			stop_step(blazko);
		}
		if (event.key.keysym.sym == SDLK_RIGHT)
		{
			blazko->player.turn_direction = 0;
			stop_step(blazko);
		}
		if (event.key.keysym.sym == SDLK_LEFT)
		{
			blazko->player.turn_direction = 0;
			stop_step(blazko);
		}
	}
	return ;
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
		disco_move = random();
		palet.a = (color & disco_move) >> 24;
		palet.r = (color & disco_move) >> 16;
		palet.g = (color & disco_move) >> 8;
		palet.b = (color & disco_move);
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
	uint32_t color_from_tex;
	t_v2int	offset;
	
	
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
		while (++y < blazko->rays[q].draw_start)
			blazko->color_buffer[(WIN_WIDTH * y) + q] = blazko->sound.is_m ? rand() : 0xFF440011; //((blazko->rays[q].hit_is_vert) 
										//? make_darkness(0xFF110044, luminess * 0.6) : make_darkness(0xFF110044, luminess));//0xFF110044;
		
		if (blazko->rays[q].hit_is_vert) 
			offset.x = ((int)blazko->rays[q].wall_hit.y) % TEXTURE_HEIGHT;
		else 
			offset.x = ((int)blazko->rays[q].wall_hit.x) % TEXTURE_WIDTH;

		y -= 1;
		int texture_index = (blazko->rays[q].hit_side);
		while(++y < blazko->rays[q].draw_end)
		{
			if (q == WIN_WIDTH / 2)
				printf("stop\n");
			float luminess = (perpendicular_dist / (float)TILE_SIZE) * 0.1f;
			int from_top = (y + (blazko->rays[q].wall_height / 2) - (WIN_HEIGHT / 2));
			offset.y = from_top * ((float)TEXTURE_HEIGHT / blazko->rays[q].wall_height);
			uint32_t color_from_tex = blazko->textures[texture_index][(TEXTURE_WIDTH * offset.y) + offset.x];
			blazko->color_buffer[(WIN_WIDTH * y) + q] = make_darkness(color_from_tex, luminess, blazko->rays[q].hit_is_vert, blazko->sound.is_m);			//(blazko->rays[q].hit_is_vert ? 0xFFFFFFFF : 0xFFBBCCDD);
		}
		y -= 1;
		while(++y < WIN_HEIGHT)
			blazko->color_buffer[(WIN_WIDTH * y) + q] = ( blazko->sound.is_m ? rand() & 0x88660022 : 0xFF220011);
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

	render_color_buf(blazko);
	clear_color_buf(blazko->color_buffer, 0xFF333333);

	render_map(blazko);
	render_rays(blazko);
	render_player(blazko);
	
	SDL_RenderPresent(blazko->render);
}

void	music_on(t_wolf3d *blazko)
{	
	blazko->sound.badmusic = NULL;
	if(Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 4096))
		ft_error("very bad music");
	blazko->sound.badmusic = Mix_LoadMUS("sound/music.ogg");
	blazko->sound.step = Mix_LoadWAV("sound/step.ogg");
	if (blazko->sound.badmusic == NULL || blazko->sound.step == NULL)
		ft_error("very bad music");
	Mix_AllocateChannels(10);
	Mix_VolumeMusic(15);
}


int		main(int argc, char **argv)
{
	int fd;
	int game_on = 0;
	long long ticks_last_frame;
	t_wolf3d *blazko = NULL;
	
	if (argc != 2 || (fd = open(argv[1], O_RDONLY)) < 0)
		ft_error("usage: ./wolf3d map");
	if (!(blazko = (t_wolf3d*)malloc(sizeof(t_wolf3d))))
		ft_error("Malloc not OK \{~_~}/\n");
	ticks_last_frame = SDL_GetTicks();
	if (!(game_on = init(blazko)))
		return(1);
	if (file_parser(blazko, fd))
		create_map(blazko);
	setup(blazko);
	music_on(blazko);
	while(game_on)
	{
		input(&game_on, blazko);
		update(blazko, &ticks_last_frame);
		make_a_move(blazko, ticks_last_frame);
		render(blazko);
	}
	destroy(blazko);
	return(0);
}