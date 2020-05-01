#include "../includes/wolf3d.h"

void		texturembo(t_wolfec *w)
{
	if ((w->surf[0][0] = IMG_Load("./textures/tekwall4.xpm")) == NULL)
		ft_error((char*)SDL_GetError());
	if ((w->surf[0][1] = IMG_Load("./textures/tekwall4.xpm")) == NULL)
		ft_error((char*)SDL_GetError());
	if ((w->surf[0][2] = IMG_Load("./textures/tekwall4.xpm")) == NULL)
		ft_error((char*)SDL_GetError());
	if ((w->surf[0][3] = IMG_Load("./textures/tekwall4.xpm")) == NULL)
		ft_error((char*)SDL_GetError());
}
