
#include "../includes/wolf3d.h"


t_wolfec	*preparation(void)
{
	t_wolfec *w;
	if (!(w = (t_wolfec *)malloc(sizeof(t_wolfec))))
		ft_error("malloc fuckup");
	if (WIDTH < 0 || WIDTH > 1920 || HEIGHT < 0 || HEIGHT > 1080)
		ft_error("Are you shitting me? Choose other window size kid\n");
	if (!(w->params_list = (t_pars_list *)malloc(sizeof(t_pars_list))))
		ft_error("malloc fuckup");
	w->pos.fov = VIEWINGWIDTH;
	w->pos.angle = 90; // random()
	w->pos.rot_speed = ROTATIONSPEED;
	w->pos.mov_speed = MOVESPEED;
	w->params_list->line = NULL;
	w->params_vars.line = NULL;
	w->params_vars.line_width = 0;
	w->params_vars.minus_one_found = 0;
	w->params_vars.tmp = w->params_list;
	w->params_vars.number_of_lines = 0;
	w->count.i2 = 0;
	w->count.i3 = 0;
	pthread_mutex_init(&w->mthread, NULL);
	return (w);
}



void	create_map(t_wolfec *w)
{
	w->count.i = -1;
	if (!(w->map = (int **)malloc(sizeof(int *) * (w->params_vars.number_of_lines + 2))))
		ft_error("malloc fuckup");
	while (++w->count.i < w->params_vars.number_of_lines + 2)
		if (!(w->map[w->count.i] = malloc(sizeof(int) * (w->params_vars.line_width + 2))))
			ft_error("malloc fuckup");
	w->count.i = 0;
	w->params_vars.tmp = w->params_list;
	put_values_in_map(w);
}


void	init_sdl(t_wolfec *w)
{
	if (SDL_Init(SDL_INIT_VIDEO))
		ft_error("initialize sdl fuckup");
	if (!(w->win = SDL_CreateWindow("wolf3d", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0)))
		ft_error("create window fuckup");
	if (!(w->rend = SDL_CreateRenderer(w->win, -1, SDL_RENDERER_SOFTWARE)))
		ft_error("create renderer fuckup");
	if (!(w->back = SDL_CreateTexture(w->rend, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGHT)))
		ft_error("create background texture fuckup");
}