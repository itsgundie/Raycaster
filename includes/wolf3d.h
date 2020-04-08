#ifndef WOLF3D_H
# define WOLF3D_H

# define WIDTH 1000
# define HEIGHT 700
# define VIEWINGWIDTH 55
# define ROTATIONSPEED 0.2
# define MOVESPEED 0.1

# include "../libft/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <pthread.h>
# include "../sdl2/2.0.12/include/SDL2/SDL.h"
# include "../sdl2/2.0.12/include/SDL2/SDL_surface.h"
# include "../sdl2/2.0.12/include/SDL2/SDL_video.h"
# include "../sdl2/2.0.12/include/SDL2/SDL_render.h"
# include "../sdl2/2.0.12/include/SDL2/SDL_pixels.h"
# include "../sdl2/2.0.12/include/SDL2/SDL_events.h"
# include "../sdl2_image/2.0.5/include/SDL2/SDL_image.h"

// # include "../SDL/SDL_surface.h"
// # include "../SDL/SDL_video.h"
// # include "../SDL/SDL_render.h"
// # include "../SDL/SDL_pixels.h"
// # include "../SDL/SDL_events.h"
// # include "../SDL/SDL_image.h"

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
	int					x;
	int					y;
	int					angle;
	int					fov;
	float				rot_speed;
	float				mov_speed;		
}								t_position;

typedef struct					s_counters
{
	int					i;
	int					i2;
	int					i3;	
}								t_counters;

typedef struct					s_wolfec
{
	t_pars_vars			params_vars;
	t_pars_list 		*params_list;
	pthread_mutex_t		mthread;
	t_position 			pos;
	t_counters			count;
	int					**map;
	SDL_Window			*win;
	SDL_Renderer		*rend;
	SDL_Texture			*back;
}								t_wolfec;

t_wolfec	*preparation(void);
int			file_parser(t_wolfec *w, int fd);
void		add_string_in_list(t_wolfec *w);
int			check_line(t_wolfec *w);
void		delete_data(t_wolfec *w);
int			check_line_width(t_wolfec *w);
void		create_map(t_wolfec *w);
void		put_values_in_map(t_wolfec *w);

#endif
