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

int		main(int argc, char **argv)
{
    int fd;
	t_wolfec *w;
	SDL_Event	event;
	const Uint8	*keyboard_state;

    fd = 0;
    if (argc != 2 || (fd = open(argv[1], O_RDONLY)) < 0)
		ft_error("\033[0;32musage: ./wolf3d map");
    w = preparation();
	if (file_parser(w, fd))
		create_map(w);
	init_sdl(w);
	predraw(w);
	texturembo(w);
	while (event.type != SDL_QUIT)
	{
		set_mouse(w);
		events(w, &event, keyboard_state);
		if (event.type == SDL_QUIT)
			break ;
		move(w, keyboard_state);
		update(w);
		render_it(w);
	}
	return (0);
}