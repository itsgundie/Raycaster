/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amargy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 19:05:27 by amargy            #+#    #+#             */
/*   Updated: 2020/05/14 19:06:46 by amargy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int		check_line(t_wolf3d *blazko)
{
	if (blazko->params_vars.line[0] == '\0')
		return (0);
	while (blazko->params_vars.line[blazko->count.i] != '\0')
	{
		while (blazko->params_vars.line[blazko->count.i] == ' ')
			blazko->count.i++;
		if (blazko->params_vars.line[blazko->count.i] == '\0')
			return (1);
		if (blazko->params_vars.line[blazko->count.i] == '-'
		&& blazko->params_vars.line[blazko->count.i + 1] == '1')
		{
			blazko->params_vars.minus_one_found++;
			blazko->params_vars.line_width++;
			if (blazko->params_vars.minus_one_found > 1)
				ft_error("Input error: need one -1 on map");
			blazko->count.i += 2;
		}
		else if ((blazko->params_vars.line[blazko->count.i] >= '0'
		&& blazko->params_vars.line[blazko->count.i] <= '9'))
			blazko->params_vars.line_width++;
		else
			return (0);
		blazko->count.i++;
	}
	return (1);
}

void	add_string_in_list(t_wolf3d *blazko)
{
	blazko->params_vars.tmp->line = blazko->params_vars.line;
	blazko->params_vars.tmp->next = (t_pars_list *)malloc(sizeof(t_pars_list));
	blazko->params_vars.tmp = blazko->params_vars.tmp->next;
	blazko->params_vars.tmp->next = NULL;
	blazko->params_vars.tmp->line = NULL;
}

int		check_line_width(t_wolf3d *blazko)
{
	if (blazko->params_vars.params_list->line == NULL)
		blazko->params_vars.tmp_line_width = blazko->params_vars.line_width;
	if (blazko->params_vars.tmp_line_width != blazko->params_vars.line_width)
	{
		destroy(blazko);
		ft_error("Map must be rectangle or squared");
	}
	return (1);
}

int		file_parser(t_wolf3d *blazko, int fd)
{
	while (get_next_line(fd, &blazko->params_vars.line) == 1)
	{
		blazko->params_vars.number_of_lines++;
		blazko->count.i = 0;
		blazko->params_vars.line_width = 0;
		if ((check_line(blazko) && check_line_width(blazko)))
			add_string_in_list(blazko);
		else
			ft_error("Input error");
	}
	if (blazko->params_vars.minus_one_found == 0)
		ft_error("Input error: need one -1 on map");
	return (1);
}
