/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cspare <cspare@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 00:04:10 by cspare            #+#    #+#             */
/*   Updated: 2020/05/29 00:31:40 by cspare           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <limits.h>
# include <math.h>
# include "../libft/libft.h"
# include <time.h>

# include "SDL.h"
# include "SDL_mixer.h"
# include "SDL_image.h"
# include "SDL_ttf.h"

# define TRUE			1
# define FALSE			0

# define PI				3.14159265
# define TWO_PI			6.28318530

# define TILE_SIZE		128
# define TEXTURE_WIDTH	128
# define TEXTURE_HEIGHT	128

# define MAP_COLUMNS 	20
# define MAP_ROWS		13
# define NUM_OF_TEXTURES	5

# define MINIMAP_SCALE 	0.125

# define WIN_WIDTH 		1280
# define WIN_HEIGHT 	720
# define WIN_TITLE		"IDEAS_FROM_THE_DEEP"

# define FOV				66

# define RAYS_NUM		WIN_WIDTH

# define FPS				60
# define MOVE_SPEED 		6
# define ROTATION_SPEED 	4

# define TEXTURE_0 		"./textures/north.png"
# define TEXTURE_1 		"./textures/fry.png"
# define TEXTURE_2 		"./textures/south.png"
# define TEXTURE_3 		"./textures/laughing_man.png"
# define TEXTURE_4 		"./textures/over_the_line.png"

typedef struct			s_v2int
{
	int					x;
	int					y;
}						t_v2int;
typedef struct			s_v2
{
	float				x;
	float				y;
}						t_v2;

typedef struct			s_argb
{
	uint32_t			a;
	uint32_t			r;
	uint32_t			g;
	uint32_t			b;
}						t_argb;

typedef struct			s_2dmap
{
	int					**map;
	int					rows;
	int					columns;
}						t_2dmap;

typedef struct			s_counters
{
	int					i;
	int					i2;
	int					i3;
	int					i4;
}						t_counters;

typedef struct			s_pars_list
{
	char				*line;
	struct s_pars_list	*next;
}						t_pars_list;

typedef struct			s_pars_vars
{
	char				*line;
	int					line_width;
	int					tmp_line_width;
	t_pars_list			*tmp;
	int					minus_one_found;
	int					number_of_lines;
	t_pars_list			*params_list;
}						t_pars_vars;

typedef struct			s_ray
{
	float				angle;
	t_v2				wall_hit;
	int					hit_is_vert;
	int					hit_is_horz;
	float				distance;
	int					wall_height;
	int					draw_start;
	int					draw_end;
	int					ray_is_up;
	int					ray_is_left;
	int					ray_is_down;
	int					ray_is_right;
	int					hit_side;
}						t_ray;

typedef struct			s_player
{
	t_v2				pos;
	float				fov;
	float				width;
	float				height;
	int					turn_direction;
	int					walk_direction;
	float				rot_angle;
	float				move_speed;
	float				rotate_speed;
}						t_player;

typedef struct			s_raycast
{
	t_v2				intercept;
	t_v2				step;
	t_v2				next;
	t_v2				check;
}						t_raycast;

typedef struct			s_sound
{
	int					is_m;
	Mix_Chunk			*s1;
	Mix_Chunk			*s2;
	Mix_Chunk			*s3;
	Mix_Chunk			*s4;
	Mix_Chunk			*s5;
	Mix_Chunk			*s6;
	Mix_Music			*badmusic;
}						t_sound;

typedef	struct			s_wolf3d
{
	SDL_Window			*window;
	SDL_Renderer		*render;
	SDL_Texture			*color_tex;
	SDL_Surface			*surfs_for_texes[NUM_OF_TEXTURES];
	t_ray				rays[WIN_WIDTH];
	t_sound				sound;
	t_2dmap				map;
	t_counters			count;
	t_pars_vars			params_vars;
	t_player			player;
	uint32_t			*wall_texture;
	uint32_t			*color_buffer;
	uint32_t			*textures[NUM_OF_TEXTURES];
	int					frame_time;
}						t_wolf3d;

int						main(int argc, char **argv);
int						file_parser(t_wolf3d *blazko, int fd);
void					add_string_in_list(t_wolf3d *blazko);
int						check_line(t_wolf3d *blazko);
void					delete_data(t_wolf3d *blazko);
int						check_line_width(t_wolf3d *blazko);
void					create_map(t_wolf3d *blazko);
void					put_values_in_map(t_wolf3d *blazko);
void					slayer_position(t_wolf3d *blazko);
void					destroy(t_wolf3d *blazko);
t_wolf3d				*init();
int						error_exit(char *str, t_wolf3d *blazko);
void					setup(t_wolf3d *blazko);
int						find_an_obstacle(float x, float y, t_2dmap *kapta);
void					make_a_move(t_wolf3d *blazko, float delta_time);
float					normalize_angle(float angle);
float					calc_distance(float x1, float y1, float x2, float y2);
void					cast_this_ray(t_wolf3d *blazko, t_ray *this_ray);
int						is_looking_down(float angle);
int						is_looking_right(float angle);
void					raycast(t_wolf3d *blazko);
void					render_player(t_wolf3d *blazko);
void					render_map(t_wolf3d *blazko);
void					render_rays(t_wolf3d *blazko);
void					update(t_wolf3d *blazko, long long *ticks_last_frame);
void					make3d(t_wolf3d *blazko);
void					clear_color_buf(uint32_t *color_buf, uint32_t color);
void					render_color_buf(t_wolf3d *blazko);
void					render(t_wolf3d *blazko);
void					music_on(t_wolf3d *blazko);
int						fck(t_wolf3d *blazko);
uint32_t				make_darkness(uint32_t color, float intensity,
						int is_vertical, int disco);
void					stop_step(t_wolf3d *blazko);
void					play_step(t_wolf3d *blazko);
void					texture_manager(t_wolf3d *blazko);
int						put_in(t_wolf3d *blazko);
int						key_down(t_wolf3d *blazko, SDL_Event event);
void					key_up(t_wolf3d *blazko, SDL_Event event);
void					music_on_off(t_wolf3d *blazko);
void					render_rectangle(t_wolf3d *blazko, int tile_y,
						int tile_x, int color);
void					render_line(t_wolf3d *blazko, t_v2int start,
						int end_x, int end_y);
void					find_wall_side(t_ray *this_ray, t_2dmap *kapta);
void					calc_horz_step(t_wolf3d *blazko, t_ray *this_ray,
						t_raycast *hor);
void					calc_vert_step(t_wolf3d *blazko, t_ray *this_ray,
						t_raycast *vert);
void					horz_intersect(t_wolf3d *blazko, t_ray *this_ray);
void					vert_intersect(t_wolf3d *blazko, t_ray *this_ray);
void					get_distance(t_wolf3d *blazko, t_ray *vert_ray,
						t_ray *hor_ray);
void					draw_ceiling(t_wolf3d *blazko, t_ray *this_ray,
						int *y, int x);
void					draw_walls(t_wolf3d *blazko, t_ray *this_ray,
						int *y, int x);
void					draw_floor(t_wolf3d *blazko, t_ray *this_ray,
						int *y, int x);
void					sacrifice_to_norme(t_raycast *tmp);
void					more_destruction(t_wolf3d *blazko, int q);
void					not_my_tempo(t_wolf3d *blazko);
int						smokers_atoi(char *str);

#endif
