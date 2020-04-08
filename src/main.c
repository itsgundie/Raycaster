#include "../includes/wolf3d.h"



void	delete_data(t_wolfec *w)
{
	t_pars_list *tmp;

	while (w->params_list != NULL)
	{
		tmp = w->params_list->next;
		free(w->params_list);
		w->params_list = tmp;
	}
	free(w);
}



int				key_event(const Uint8 *keyboard_state, t_wolfec *w)
{
	if (keyboard_state[SDL_SCANCODE_LSHIFT])
		w->pos.mov_speed = fabs(MOVESPEED) * 2;
	else
		w->pos.mov_speed = fabs(MOVESPEED);
	if (keyboard_state[SDL_SCANCODE_ESCAPE])
		return (1);
	return (0);
}



int		main(int argc, char **argv)
{
    int fd;
	t_wolfec *w;

    fd = 0;
    if (argc != 2 || (fd = open(argv[1], O_RDONLY)) < 0)
		ft_error("\033[0;32musage: ./wolf3d map");
    w = preparation();
	if (file_parser(w, fd))
		create_map(w);
	init_sdl(w);
	while(!close_the_game)
	{
		predraw(w);
		display(w);
	}
	return (0);
}