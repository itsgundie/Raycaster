
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "SDL.h"

#define TRUE		1
#define FALSE		0

#define PI			3.14159265
#define TWO_PI		6.28318530

#define TILE_SIZE	128
#define TEXTURE_WIDTH	128
#define TEXTURE_HEIGHT	128
#define MAP_COLUMNS 20
#define MAP_ROWS	13

#define MINIMAP_SCALE	0.1

#define WIN_WIDTH 	1280
#define WIN_HEIGHT 	720
#define WIN_TITLE	"IDEAS_FROM_THE_DEEP"

#define FOV			66

#define RAYS_NUM	WIN_WIDTH

#define FPS			30
#define FRAME_TIME	(1000 / FPS)





const int map[MAP_ROWS][MAP_COLUMNS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

typedef struct	s_v2int
{
	int			x;
	int			y;
}				t_v2int;


typedef struct	s_v2
{
	float		x;
	float		y;
}				t_v2;

typedef struct	s_ray
{
	float		angle;
	t_v2		wall_hit;
	int			hit_is_vert;
	float		distance;
	int			wall_height;
	int			draw_start;
	int			draw_end;
	int			ray_is_up;
	int			ray_is_left;
	int			ray_is_down;
	int			ray_is_right;
	int			hit_side;
}				t_ray;

typedef struct	s_player
{
	t_v2		pos;
	float		fov;
	float		width;
	float		height;
	int			turn_direction;
	int			walk_direction;
	float		rotation_angle;
	float		move_speed;
	float		rotate_speed;
}				t_player;

typedef struct		s_wolf3d
{
	SDL_Window*		window;
	SDL_Renderer*	render;
	SDL_Texture*	color_tex;
	uint32_t*		wall_texture;
	t_player		player;
	t_ray			rays[WIN_WIDTH];
	uint32_t*		color_buffer;
}				t_wolf3d;

int		init(t_wolf3d *blazko)
{
	blazko->window = NULL;
	blazko->render = NULL;
	blazko->wall_texture = NULL;
	blazko->color_buffer = NULL;
	blazko->color_tex = NULL;

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

void	destroy(t_wolf3d *blazko)
{
	int q;

	q = -1;
	// free(blazko->color_buffer);
	// while (blazko->wall_textures[q])
	// 	free(blazko->wall_textures[q])
	// blazko->color_buffer = NULL;
	// blazko->wall_textures = NULL;
	SDL_DestroyRenderer(blazko->render);
	SDL_DestroyWindow(blazko->window);
	SDL_Quit();
}

int		error_exit(char *str, t_wolf3d *blazko)
{
	printf("%s", str);
	destroy(blazko);
	exit(1);
}

void	setup(t_wolf3d *blazko)
{
	int x;
	int y;

	x = -1;
	y = -1;
	
	if (!(blazko->color_buffer = (uint32_t*)malloc(sizeof(uint32_t) 
					* (uint32_t)WIN_WIDTH * (uint32_t)WIN_HEIGHT)))
		error_exit("Malloc Not OK -_-\n", blazko);
	blazko->color_tex = SDL_CreateTexture(blazko->render,
	 	SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIN_WIDTH, WIN_HEIGHT);
	if (!(blazko->wall_texture = (uint32_t*)malloc(sizeof(uint32_t) 
					* (uint32_t)TEXTURE_WIDTH * (uint32_t)TEXTURE_HEIGHT)))
		error_exit("Malloc Not OK, Particularly the wall texture -_-\n", blazko);
	bzero(blazko->wall_texture, (sizeof(uint32_t) * (uint32_t)TEXTURE_HEIGHT * (uint32_t)TEXTURE_WIDTH));
	while (++y < TEXTURE_HEIGHT)
	{
		x = -1;
		while (++x < TEXTURE_WIDTH)
		{
			uint32_t border = rand() % rand();
			uint32_t fill = rand() / rand();
			blazko->wall_texture[TEXTURE_WIDTH * y + x] = (((x % 8 < rand()) && ((y / 8 < rand())) ? fill : border));
		}
		//0xFF888888 : 0xFF223344
	}
	blazko->player.pos.x = WIN_WIDTH / 2;
	blazko->player.pos.y = WIN_HEIGHT / 2;
	blazko->player.width = 1;
	blazko->player.height = 1;
	blazko->player.turn_direction = 0;
	blazko->player.walk_direction = 0;
	blazko->player.rotation_angle = PI / 2;
	blazko->player.fov = (FOV * (PI / 180));
	blazko->player.move_speed = 5;
	blazko->player.rotate_speed = 5 * (PI / 180);
}

int		find_an_obstacle(float x, float y)
{
	t_v2int check;

	if (x < 0 || x > (MAP_COLUMNS * TILE_SIZE) || y < 0 || y > (MAP_ROWS * TILE_SIZE))
		return (TRUE);
	check.x = (int)(x / TILE_SIZE);
	check.y = (int)(y / TILE_SIZE);
	return(map[check.y][check.x] != 0);
}

void	make_a_move(t_wolf3d *blazko, float delta_time)
{
	float move_step;
	t_v2	new_pos;

	blazko->player.rotation_angle += ((blazko->player.turn_direction) * (blazko->player.rotate_speed)); //* delta_time);
	move_step = blazko->player.walk_direction * blazko->player.move_speed; //* delta_time;
	new_pos.x = blazko->player.pos.x + cos(blazko->player.rotation_angle) * move_step;
	new_pos.y = blazko->player.pos.y + sin(blazko->player.rotation_angle) * move_step;

	if (!find_an_obstacle(new_pos.x ,new_pos.y))
	{
		blazko->player.pos.x = new_pos.x;
		blazko->player.pos.y = new_pos.y;
	}
}

float	normalize_angle(float angle)
{
	float norm_angle;
	norm_angle = remainder(angle, TWO_PI);
	if (norm_angle < 0)
		norm_angle = TWO_PI + norm_angle;
	return(norm_angle);
}

float calc_distance(float x1, float y1, float x2, float y2)
{
	return(sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	cast_this_ray(t_wolf3d *blazko, t_ray *this_ray)
{
	// t_v2 intercept;
	// t_v2 step;
	// t_v2 check;
	// t_ray tmp_ray;
	// t_v2 next;
	// t_v2 hor_hit;
	// int	side_index_hor;
	// int	hit_hor_wall;
	// t_v2 ver_hit;
	// int hit_ver_wall;
	// int side_index_ver;
	// t_v2 next_ver;
	// t_v2 check_ver;

	t_v2 intercept_hor;
	t_v2 step_hor;
	t_v2 next_hor;
	t_v2 check_hor;
	t_v2 hit_point_hor = {0};
	int	 was_hit_horizont = FALSE;
	int side_index_hor = 0;


	// Horizontal intersection //
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

	while (next_hor.x >= 0 && next_hor.x <= (MAP_COLUMNS * TILE_SIZE)
			&& next_hor.y >= 0 && next_hor.y <= (MAP_ROWS * TILE_SIZE))
	{
		check_hor.x = next_hor.x;
		check_hor.y = next_hor.y + (this_ray->ray_is_up ? -1 : 0);

		if (find_an_obstacle(check_hor.x, check_hor.y))
		{
			hit_point_hor.x = next_hor.x;
			hit_point_hor.y = next_hor.y;

			side_index_hor = map[(int)floor(check_hor.y / TILE_SIZE)]
								[(int)floor(check_hor.x / TILE_SIZE)];
			was_hit_horizont = TRUE;
			break;
		}
		else
		{
			next_hor.x += step_hor.x;
			next_hor.y += step_hor.y;
		}
	}	

	/// VERTICAL INTERSECTION ///

	t_v2 intercept_ver;
	t_v2 step_ver;
	t_v2 next_ver;
	t_v2 check_ver;
	t_v2 hit_point_ver = {0};
	int	 was_hit_vert = FALSE;
	int side_index_ver = 0;

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

	while (next_ver.x >= 0 && next_ver.x <= (MAP_COLUMNS * TILE_SIZE) 
		&& next_ver.y >= 0 && next_ver.y <= (MAP_ROWS * TILE_SIZE))
	{
		check_ver.x = next_ver.x + (this_ray->ray_is_left ? -1 : 0);
		check_ver.y = next_ver.y;

		if (find_an_obstacle(check_ver.x, check_ver.y))
		{
			 hit_point_ver.x = next_ver.x;
			 hit_point_ver.y = next_ver.y;
			 side_index_ver = map[(int)floor(check_ver.y / TILE_SIZE)][(int)floor(check_ver.x / TILE_SIZE)];
			 was_hit_vert = TRUE;
			 break;
		}
		else
		{
			next_ver.x += step_ver.x;
			next_ver.y += step_ver.y;
		}
		
	}

	//// DISTANCE ///

	float distance_hor = (was_hit_horizont ? 
		calc_distance(blazko->player.pos.x, blazko->player.pos.y, hit_point_hor.x, hit_point_hor.y) : INT_MAX);
	
	float distance_ver = (was_hit_vert ? 
		calc_distance(blazko->player.pos.x, blazko->player.pos.y, hit_point_ver.x, hit_point_ver.y) : INT_MAX);
	
	if (distance_ver < distance_hor)
	{
		this_ray->distance = (distance_ver <= 0 ? 1 : distance_ver);
		this_ray->wall_hit.x = hit_point_ver.x;
		this_ray->wall_hit.y = hit_point_ver.y;
		this_ray->hit_side = side_index_ver;
		this_ray->hit_is_vert = TRUE;
	}
	else
	{
		{
		this_ray->distance = (distance_hor <= 0 ? 1 : distance_hor);
		this_ray->wall_hit.x = hit_point_hor.x;
		this_ray->wall_hit.y = hit_point_hor.y;
		this_ray->hit_side = side_index_hor;
		this_ray->hit_is_vert = FALSE;
	}
	}
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


void	render_player(t_wolf3d *blazko)
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

void	render_map(t_wolf3d *blazko)
{
	int j;
	int k;

	j = 0;
	k = 0;

	while (j < MAP_ROWS)
	{
		k = 0;
		while (k < MAP_COLUMNS)
		{
			int tile_x = (k * TILE_SIZE);
			int tile_y = (j * TILE_SIZE);
			int tile_color = map[j][k] != 0 ? 255 : 0;
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
		if (event.key.keysym.sym == SDLK_ESCAPE)
			*game_on = FALSE;
		if (event.key.keysym.sym == SDLK_UP)
			blazko->player.walk_direction = +1;
		if (event.key.keysym.sym == SDLK_DOWN)
			blazko->player.walk_direction = -1;
		if (event.key.keysym.sym == SDLK_RIGHT)
			blazko->player.turn_direction = +1;
		if (event.key.keysym.sym == SDLK_LEFT)
			blazko->player.turn_direction = -1;
	}
	else if (event.type == SDL_KEYUP)
	{
		if (event.key.keysym.sym == SDLK_UP)
			blazko->player.walk_direction = 0;
		if (event.key.keysym.sym == SDLK_DOWN)
			blazko->player.walk_direction = 0;
		if (event.key.keysym.sym == SDLK_RIGHT)
			blazko->player.turn_direction = 0;
		if (event.key.keysym.sym == SDLK_LEFT)
			blazko->player.turn_direction = 0;
	}
	return ;
}

void	update(t_wolf3d *blazko, long long *ticks_last_frame)
{
	int time_to_wait;
	time_to_wait = FRAME_TIME - (SDL_GetTicks() - *ticks_last_frame);

	if (time_to_wait > 0 && time_to_wait <= FRAME_TIME)
		SDL_Delay(time_to_wait);

	while(!(SDL_TICKS_PASSED(SDL_GetTicks(), (*ticks_last_frame + FRAME_TIME))));

	float delta_time = (SDL_GetTicks() - *ticks_last_frame) * 1000.0f;
	*ticks_last_frame = SDL_GetTicks();
	make_a_move(blazko, delta_time);
	raycast(blazko);


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
			blazko->color_buffer[(WIN_WIDTH * y) + q] = 0xFF440011;
		
		if (blazko->rays[q].hit_is_vert) 
			offset.x = ((int)blazko->rays[q].wall_hit.y) % TEXTURE_HEIGHT;
		else 
			offset.x = ((int)blazko->rays[q].wall_hit.x) % TEXTURE_WIDTH;

		y -= 1;
		while(++y < blazko->rays[q].draw_end)
		{
			int from_top = (y + (blazko->rays[q].wall_height / 2) - (WIN_HEIGHT / 2));
			offset.y = from_top * ((float)TEXTURE_HEIGHT / blazko->rays[q].wall_height);
			uint32_t color_from_tex = blazko->wall_texture[(TEXTURE_WIDTH * offset.y) + offset.x];
			blazko->color_buffer[(WIN_WIDTH * y) + q] = color_from_tex;			//(blazko->rays[q].hit_is_vert ? 0xFFFFFFFF : 0xFFBBCCDD);
		}
		y -= 1;
		while(++y < WIN_HEIGHT)
			blazko->color_buffer[(WIN_WIDTH * y) + q] = 0xFF220000;
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


int		main(void)
{
	int game_on = 0;
	long long ticks_last_frame;
	t_wolf3d *blazko = NULL;
	
	ticks_last_frame = SDL_GetTicks();

	if (!(blazko = (t_wolf3d*)malloc(sizeof(t_wolf3d))))
		printf("Malloc not OK \{~_~}/\n");
	if (!(game_on = init(blazko)))
		return(1);
	setup(blazko);
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
