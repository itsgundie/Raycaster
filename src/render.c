
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

int		load_textures(t_wolfec *tex, unsigned int index)
{
	SDL_Surface		*Surf;
	const char		*path;
	
	Surf = NULL;

	if (index == 0)
		path = TEXTURE_FOR_0;
	if (index == 1)
		path = TEXTURE_FOR_1;
	if (index == 2)
		path = TEXTURE_FOR_2;
	if (index == 3)
		path = TEXTURE_FOR_3;
	if (index == 4)
		path = TEXTURE_FOR_4;
	if (index == 5)
		path = TEXTURE_FOR_5;
	if (index == 6)
		path = TEXTURE_FOR_6;
	if ((!(Surf = IMG_Load(path))) || !(texes[index] = SDL_CreateTextureFromSurface(w->rend, Surf)))
		return(0);	
	SDL_FreeSurface(Surf);
	return(1);
}

void	texturizer(t_wolfec *w)
{
	unsigned int			q;

	q = 0;

	while(q <= TEXTURE_PACK_SIZE)
	{
		if (!(load_textures(w, q)))
			ft_error("Textures loading error\n"); //	Replace string with code and add explanation to function
		q++;
	}
	return(texs);
}



void	render_it(t_wolfec *w)
{
	SDL_RenderCopy(w->rend, w->back, NULL, NULL);
	SDL_RenderPresent(w->rend);
}