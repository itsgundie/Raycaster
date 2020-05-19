/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amargy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 16:34:23 by amargy            #+#    #+#             */
/*   Updated: 2020/05/16 13:12:34 by amargy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/wolf3d.h>

void	setup(t_wolf3d *blazko)
{
	blazko->color_buffer = NULL;
	blazko->color_tex = NULL;
	texture_manager(blazko);
	blazko->player.width = 1;
	blazko->player.height = 1;
	blazko->player.turn_direction = 0;
	blazko->player.walk_direction = 0;
	blazko->player.rotation_angle = TWO_PI;
	blazko->player.fov = (FOV * (PI / 180));
	blazko->player.move_speed = 5;
	blazko->player.rotate_speed = 5 * (PI / 180);
	blazko->frame_time = 1000 / FPS;
	blazko->map.columns = blazko->params_vars.line_width + 2;
	blazko->map.rows = blazko->params_vars.number_of_lines + 2;
}

int		init2(t_wolf3d *blazko)
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
	//SDL_SetRenderDrawBlendMode(blazko->render, SDL_BLENDMODE_MOD);
	return (TRUE);
}

int		init(t_wolf3d *blazko)
{
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
	return (TRUE);
}
