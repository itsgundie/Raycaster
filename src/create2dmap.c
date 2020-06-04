/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create2dmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amargy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 18:05:27 by amargy            #+#    #+#             */
/*   Updated: 2020/05/14 19:06:46 by amargy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	slayer_position(t_wolf3d *blazko)
{
	if (blazko->params_vars.tmp->line[blazko->count.i2] == '-'
	&& blazko->params_vars.tmp->line[blazko->count.i2 + 1] == '1')
	{
		blazko->player.pos.x = blazko->count.i3 * TILE_SIZE + TILE_SIZE / 2;
		blazko->player.pos.y = blazko->count.i * TILE_SIZE + TILE_SIZE / 2;
	}
}

int		smokers_atoi(char *str)
{
	int	result;

	if (str[0] == '-')
		result = -1;
	else
		result = str[0] - '0';
	return (result);
}

int		fck(t_wolf3d *blazko)
{
	slayer_position(blazko);
	if (blazko->params_vars.tmp->line[blazko->count.i2] != '\0')
		blazko->count.i4 = blazko->count.i3 + 1;
	return (smokers_atoi(&blazko->params_vars.tmp->line[blazko->count.i2]));
}

void	put_values_in_map(t_wolf3d *blazko)
{
	while (blazko->count.i3 <= blazko->params_vars.line_width + 1)
		blazko->map.map[blazko->count.i][blazko->count.i3++] = 1;
	blazko->count.i3 = 0;
	while (++blazko->count.i < blazko->params_vars.number_of_lines + 1)
	{
		blazko->map.map[blazko->count.i][blazko->count.i3++] = 1;
		while (blazko->params_vars.tmp->line[blazko->count.i2] != '\0')
		{
			while (blazko->params_vars.tmp->line[blazko->count.i2] == ' ')
				blazko->count.i2++;
			blazko->map.map[blazko->count.i][blazko->count.i3] = fck(blazko);
			if (blazko->params_vars.tmp->line[blazko->count.i2] == '0'
			|| blazko->params_vars.tmp->line[blazko->count.i2] == '1')
				blazko->count.i2++;
			else if (blazko->params_vars.tmp->line[blazko->count.i2] == '-')
				blazko->count.i2 += 2;
			blazko->count.i3++;
		}
		blazko->map.map[blazko->count.i][blazko->count.i4] = 1;
		blazko->count.i2 = 0;
		blazko->count.i3 = 0;
		blazko->params_vars.tmp = blazko->params_vars.tmp->next;
	}
	while (blazko->count.i3 <= blazko->params_vars.line_width + 1)
		blazko->map.map[blazko->count.i][blazko->count.i3++] = 1;
}

void	create_map(t_wolf3d *blazko)
{
	if (blazko->params_vars.number_of_lines > 30
	|| blazko->params_vars.line_width > 30)
		error_exit("max map size - 30x30\n", blazko);
	blazko->count.i = -1;
	if (!(blazko->map.map = (int **)malloc(sizeof(int *)
	* (blazko->params_vars.number_of_lines + 2))))
		error_exit("malloc fuckup\n", blazko);
	ft_memset(blazko->map.map, 0, sizeof(blazko->map.map));
	while (++blazko->count.i < blazko->params_vars.number_of_lines + 2)
		if (!(blazko->map.map[blazko->count.i] = (int *)malloc(sizeof(int) *
		(blazko->params_vars.line_width + 2))))
			error_exit("malloc fuckup\n", blazko);
	blazko->count.i = 0;
	blazko->params_vars.tmp = blazko->params_vars.params_list;
	put_values_in_map(blazko);
	blazko->count.i = 0;
	blazko->map.columns = blazko->params_vars.line_width + 2;
	blazko->map.rows = blazko->params_vars.number_of_lines + 2;
}
