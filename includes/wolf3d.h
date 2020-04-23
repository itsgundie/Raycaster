#ifndef WOLF3D_H
# define WOLF3D_H

# define WIN_WIDTH		1000
# define WIN_HEIGHT		700
# define FOV			60
# define ROTATIONSPEED	0.2f
# define MOVESPEED		0.1f

# define PLAYER_HEIGHT		16
# define TILE_SIZE			32


# define SCREEN_SCALE 1
# define SCREEN_NAME "Proto"


/*		TEXTURES BLOCK		*/

# define TEXTURE_PACK_SIZE 6
# define TEXTURE_FOR_1		"../assets/first.png"
# define TEXTURE_FOR_2		"../assets/second.png"
# define TEXTURE_FOR_3		"../assets/third.png"
# define TEXTURE_FOR_4		"../assets/fourth.png"
# define TEXTURE_FOR_5		"../assets/ceiling.png"
# define TEXTURE_FOR_6		"../assets/floor.png"
# define TEXTURE_FOR_0		"../assets/void.png"



# include "../libft/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <pthread.h>
# include <limits.h>
# include <float.h>
# include "../SDL/inc/SDL.h"
# include "../SDL/inc/SDL_surface.h"
# include "../SDL/inc/SDL_video.h"
# include "../SDL/inc/SDL_render.h"
# include "../SDL/inc/SDL_pixels.h"
# include "../SDL/inc/SDL_events.h"
# include "../SDL/inc/SDL_image.h"

// # include "../SDL/SDL_surface.h"
// # include "../SDL/SDL_video.h"
// # include "../SDL/SDL_render.h"
// # include "../SDL/SDL_pixels.h"
// # include "../SDL/SDL_events.h"
// # include "../SDL/SDL_image.h"


typedef	struct					s_v2d_float
{
	float				x;
	float				y;
}								t_v2_float;

typedef	struct					s_v2d_int
{
	int					x;
	int					y;
}								t_v2_int;

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
}								t_pars_vars;

typedef struct					s_position
{
	t_v2_int			pos_int;
	t_v2_float			pos_float;
	float				angle;
	float				fov;
	float				rot_speed;
	float				mov_speed;
	int					look_up;
	int					look_left;	
}								t_position;

typedef struct					s_counters
{
	int					i;
	int					i2;
	int					i3;	
}								t_counters;

typedef	struct					s_ray
{
	float				angle;
	t_v2_float			pos;
	float				distance; //высота столба
	int					look_up;
	int					look_left;
	int					hit_index; //индекс текстуры

}								t_ray;

typedef struct					s_wolfec
{
	t_pars_vars			params_vars;
	t_pars_list 		*params_list;
	pthread_mutex_t		mthread;
	t_position 			player;
	t_counters			count;
	int					**map;
	int					mouse_in_win_flag;
	t_ray				ray[WIN_WIDTH];
	SDL_Window			*win;
	SDL_Renderer		*rend;
	SDL_Texture			*back;;
	SDL_Surface			*surf[1][4];
}								t_wolfec;

// int worldMap[mapWidth][mapHeight]=
// {
//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// };

t_wolfec	*preparation(void);
int			file_parser(t_wolfec *w, int fd);
void		add_string_in_list(t_wolfec *w);
int			check_line(t_wolfec *w);
void		delete_data(t_wolfec *w);
int			check_line_width(t_wolfec *w);
void		create_map(t_wolfec *w);
void		put_values_in_map(t_wolfec *w);
void		niz(t_wolfec *w);
void		verh(t_wolfec *w);
void	 	events(t_wolfec *w, SDL_Event *event, const Uint8 *keyboard_state);
void		key_eater(t_wolfec *w, SDL_Event *event, const Uint8 *keyboard_state);
void		set_mouse(t_wolfec *w);
void		init_sdl(t_wolfec *w);
void		predraw(t_wolfec *w);
void		render_it(t_wolfec *w);
void		texturembo(t_wolfec *w);
float       degrees_to_rads(float degrees);
float		normalize_angle(float angle);
int			is_looking_up(float	*angle);
int			is_looking_left(float *angle);
float		angle_between_rays(float fov);
void    	calculate_rays_angles(t_wolfec *w, float angle_step);
void   		update(t_wolfec *w);
void		find_wall(t_ray *this_ray, t_v2_int *player_pos, int **map);
t_v2_int	calc_center(int	width, int height);
float		calc_distance_projected(t_v2_int *start, t_v2_int *end, float *angle);
void		find_vertical_intersection(t_ray *this_ray, t_v2_int *player_pos, int **map);
int			find_an_obstacle(t_v2_int coords, int **map, t_ray *this_ray);
void		mouse_click(SDL_Event *event, t_wolfec *w);

#endif
