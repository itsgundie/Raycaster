#ifndef WOLF3D_H
# define WOLF3D_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "../libft/libft.h"
#include <time.h>

#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_image.h"

#define TRUE		1
#define FALSE		0

#define PI			3.14159265
#define TWO_PI		6.28318530

#define TILE_SIZE		128
#define TEXTURE_WIDTH	128
#define TEXTURE_HEIGHT	128

#define MAP_COLUMNS 20
#define MAP_ROWS	13
#define NUM_OF_TEXTURES		5

#define MINIMAP_SCALE	0.1

#define WIN_WIDTH 	1280
#define WIN_HEIGHT 	720
#define WIN_TITLE	"IDEAS_FROM_THE_DEEP"

#define FOV			66

#define RAYS_NUM	WIN_WIDTH

#define FPS			30

#define TEXTURE_0 "./textures/north.png"
#define TEXTURE_1 "./textures/fry.png"
#define TEXTURE_2 "./textures/south.png"
#define TEXTURE_3 "./textures/laughing_man.png"
#define TEXTURE_4 "./textures/over_the_line.png"


//#define WAV_PATH ""
//#define MUS_PATH "../sound/LAST.ogg"

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

typedef struct	s_argb
{
	uint32_t	a;	
	uint32_t	r;	
	uint32_t	g;	
	uint32_t	b;	
}				t_argb;

typedef struct	s_2dmap
{
	int **map;
	int	rows;
	int columns;
}				t_2dmap;

typedef struct					s_counters
{
	int					i;
	int					i2;
	int					i3;	
}								t_counters;

typedef struct					s_pars_list
{
	char				*line;
	struct s_pars_list	*next;	
}								t_pars_list;

typedef struct					s_pars_vars
{
	char				*line;
	int					line_width;
	int					tmp_line_width;
	t_pars_list			*tmp;
	int					minus_one_found;
	int					number_of_lines;
	t_pars_list 		*params_list;
}								t_pars_vars;

typedef struct	s_ray
{
	float		angle;
	t_v2		wall_hit;
	int			hit_is_vert;
	int			hit_is_horz;
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

typedef struct	s_sound
{
	int 			is_m;
	Mix_Chunk		*s1;
	Mix_Chunk		*s2;
	Mix_Chunk		*s3;
	Mix_Chunk		*s4;
	Mix_Chunk		*s5;
	Mix_Chunk		*s6;
	Mix_Chunk		*s7;
	Mix_Chunk		*s8;
	Mix_Chunk		*s9;
	Mix_Chunk		*s10;
	Mix_Chunk		*s11;
	Mix_Chunk		*s12;
	Mix_Chunk		*s13;
	Mix_Chunk		*s14;
	Mix_Chunk		*s15;
	Mix_Chunk		*s16;
	Mix_Chunk		*s17;
	Mix_Chunk		*s18;
	Mix_Chunk		*s19;
	Mix_Chunk		*s20;
	Mix_Music 		*badmusic;
}				t_sound;

typedef struct	s_wolf3d
{
	SDL_Window* 	window;
	SDL_Renderer* 	render;
	SDL_Texture*	color_tex;
	uint32_t*		wall_texture;
	uint32_t*		color_buffer;
	SDL_Surface*	surfs_for_texes[NUM_OF_TEXTURES];
	uint32_t*		textures[NUM_OF_TEXTURES];
	t_ray			rays[WIN_WIDTH];
	t_sound			sound;
	t_2dmap 		map;
	t_counters 		count;
	t_pars_vars		params_vars;
	t_player		player;
	int				frame_time;
}				t_wolf3d;

int			main(int argc, char **argv);
int			file_parser(t_wolf3d *blazko, int fd);
void		add_string_in_list(t_wolf3d *blazko);
int			check_line(t_wolf3d *blazko);
void		delete_data(t_wolf3d *blazko);
int			check_line_width(t_wolf3d *blazko);
void		create_map(t_wolf3d *blazko);
void		put_values_in_map(t_wolf3d *blazko);
void		slayer_position(t_wolf3d *blazko);
void		destroy(t_wolf3d *blazko);
int			init(t_wolf3d *blazko);
int			error_exit(char *str, t_wolf3d *blazko);
void		setup(t_wolf3d *blazko);
int			find_an_obstacle(float x, float y, t_2dmap *kapta);
void		make_a_move(t_wolf3d *blazko, float delta_time);
float		normalize_angle(float angle);
float 		calc_distance(float x1, float y1, float x2, float y2);
void		cast_this_ray(t_wolf3d *blazko, t_ray *this_ray);
int			is_looking_down(float angle);
int			is_looking_right(float angle);
void		raycast(t_wolf3d *blazko);
void		render_player(t_wolf3d *blazko);
void		render_map(t_wolf3d *blazko);
void		render_rays(t_wolf3d *blazko);
void		input(int *game_on, t_wolf3d *blazko);
void		update(t_wolf3d *blazko, long long *ticks_last_frame);
void		make3d(t_wolf3d *blazko);
void		clear_color_buf(uint32_t *color_buf, uint32_t color);
void		render_color_buf(t_wolf3d *blazko);
void		render(t_wolf3d *blazko);
void		music_on();
int			fck(t_wolf3d *blazko);
uint32_t	make_darkness(uint32_t color, float intensity, int is_vertical, int disco);
void		stop_step(t_wolf3d *blazko);
void		play_step(t_wolf3d *blazko);
#endif
