/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cspare <cspare@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 16:34:23 by amargy            #+#    #+#             */
/*   Updated: 2020/05/28 00:08:58 by cspare           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			texture_manager(t_wolf3d *blazko)
{
	int q;

	q = -1;
	if (!(blazko->color_buffer = (uint32_t*)malloc(sizeof(uint32_t)
			* (uint32_t)WIN_WIDTH * (uint32_t)WIN_HEIGHT)))
		error_exit("Malloc of color_buff Not OK -_-\n", blazko);
	if (!(blazko->color_tex = SDL_CreateTexture(blazko->render,
				SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
				WIN_WIDTH, WIN_HEIGHT)))
		error_exit("Malloc of color_tex Not OK -_-\n", blazko);
	blazko->surfs_for_texes[0] = IMG_Load(TEXTURE_0);
	blazko->surfs_for_texes[1] = IMG_Load(TEXTURE_1);
	blazko->surfs_for_texes[2] = IMG_Load(TEXTURE_2);
	blazko->surfs_for_texes[3] = IMG_Load(TEXTURE_3);
	blazko->surfs_for_texes[4] = IMG_Load(TEXTURE_4);
	while (blazko->surfs_for_texes[++q]);
	if (q < NUM_OF_TEXTURES)
		error_exit("Malloc Not OK, particularly loading textures", blazko);
	q = -1;
	while (++q < NUM_OF_TEXTURES)
		blazko->textures[q] = (uint32_t*)(blazko->surfs_for_texes[q]->pixels);
}

void			setup(t_wolf3d *blazko)
{
	blazko->color_buffer = NULL;
	blazko->color_tex = NULL;
	texture_manager(blazko);
	blazko->player.width = 1;
	blazko->player.height = 1;
	blazko->player.turn_direction = 0;
	blazko->player.walk_direction = 0;
	blazko->player.rot_angle = TWO_PI;
	blazko->player.fov = (FOV * (PI / 180));
	blazko->player.move_speed = MOVE_SPEED;
	blazko->player.rotate_speed = ROTATION_SPEED * (PI / 180);
	blazko->frame_time = 1000 / FPS;
	blazko->map.columns = blazko->params_vars.line_width + 2;
	blazko->map.rows = blazko->params_vars.number_of_lines + 2;
}

int				init2(t_wolf3d *blazko)
{
	if ((SDL_Init(SDL_INIT_EVERYTHING)))
	{
		printf("Error Initializing SDL\n");
		return (FALSE);
	}
	if (!(blazko->window = SDL_CreateWindow(WIN_TITLE, SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, 0)))
	{
		printf("Error creating SDL window\n");
		return (FALSE);
	}
	if (!(blazko->render = SDL_CreateRenderer(blazko->window, -1, 0)))
	{
		printf("Error creating SDL render\n");
		return (FALSE);
	}
	return (TRUE);
}

t_wolf3d		*init(void)
{
	t_wolf3d	*blazko;

	if (!(blazko = (t_wolf3d*)malloc(sizeof(t_wolf3d))))
		ft_error("Malloc not OK \{~_~}/\n");
	if (!(blazko = (t_wolf3d*)malloc(sizeof(t_wolf3d))))
		ft_error("Malloc not OK \{~_~}/\n");
	blazko->window = NULL;
	blazko->render = NULL;
	blazko->wall_texture = NULL;
	blazko->color_buffer = NULL;
	blazko->color_tex = NULL;
	blazko->sound.badmusic = NULL;
	blazko->sound.is_m = 0;
	if (!(blazko->params_vars.params_list = (t_pars_list *)
	malloc(sizeof(t_pars_list))))
		printf("Malloc failed\n");
	blazko->params_vars.tmp = blazko->params_vars.params_list;
	blazko->params_vars.params_list->line = NULL;
	if (!(init2(blazko)))
		return (FALSE);
	return (blazko);
}
