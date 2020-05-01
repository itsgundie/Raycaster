
#include "../includes/wolf3d.h"

int		check_line(t_wolfec *w)
{
	if (w->params_vars.line[0] == '\0')
		return (0);
	while (w->params_vars.line[w->count.i] != '\0')
	{
		while (w->params_vars.line[w->count.i] == ' ')
			w->count.i++;
		if (w->params_vars.line[w->count.i] == '-' && w->params_vars.line[w->count.i + 1] == '1')
		{
			w->params_vars.minus_one_found++;
			w->params_vars.line_width++;
			if (w->params_vars.minus_one_found > 1)
				ft_error("\033[0;31mInput error: need one -1 on map");
			w->count.i += 2;
		}
		else if	((w->params_vars.line[w->count.i] >= '0' && w->params_vars.line[w->count.i] <= '9'))
			w->params_vars.line_width++;
		else
			return (0);
		w->count.i++;
	}
	return (1);
}

void	add_string_in_list(t_wolfec *w)
{
	w->params_vars.tmp->line = w->params_vars.line;
	w->params_vars.tmp->next = (t_pars_list *)malloc(sizeof(t_pars_list));
	w->params_vars.tmp = w->params_vars.tmp->next;
	w->params_vars.tmp->next = NULL;
	w->params_vars.tmp->line = NULL;
}

int		check_line_width(t_wolfec *w)
{
	if (w->params_list->line == NULL)
		w->params_vars.tmp_line_width = w->params_vars.line_width;
	if (w->params_vars.tmp_line_width != w->params_vars.line_width)
	{
		delete_data(w);
		ft_error("\033[0;31mMap must be rectangle");		
	}
	return (1);
}

int		file_parser(t_wolfec *w, int fd)
{
	while (get_next_line(fd, &w->params_vars.line) == 1)
	{
		w->params_vars.number_of_lines++;
		w->count.i = 0;
		w->params_vars.line_width = 0;
		if ((check_line(w) && check_line_width(w)))
			add_string_in_list(w);
		else
			ft_error("\033[0;31mInput error");
	}
	if (w->params_vars.minus_one_found == 0)
		ft_error("\033[0;31mInput error: need one -1 on map");
	return (1);
}

void	slayer_position(t_wolfec *w)
{
	if (w->params_vars.tmp->line[w->count.i2] == '-' 
	&& w->params_vars.tmp->line[w->count.i2 + 1] == '1')
	{
		w->player.pos_float.x = w->count.i3 + 0.5;
		w->player.pos_float.y = w->count.i + 0.5;
	} 	
}

void	put_values_in_map(t_wolfec *w)
{
	while (w->count.i3 <= w->params_vars.line_width + 1)
		w->map[w->count.i][w->count.i3++] = 1;
	w->count.i3 = 0;
	while (++w->count.i < w->params_vars.number_of_lines + 1)
	{
		w->map[w->count.i][w->count.i3++] = 1;
		while (w->params_vars.tmp->line[w->count.i2] != '\0')
		{
			while (w->params_vars.tmp->line[w->count.i2] == ' ')
				w->count.i2++;
			w->map[w->count.i][w->count.i3] = atoi(&w->params_vars.tmp->line[w->count.i2]);
			slayer_position(w);
			while ((w->params_vars.tmp->line[w->count.i2] >= '0'
			&& w->params_vars.tmp->line[w->count.i2] <= '9')
			|| w->params_vars.tmp->line[w->count.i2] == '-')
				w->count.i2++;
			w->count.i3++;
		}
		w->map[w->count.i][w->count.i3] = 1;
		w->count.i2 = 0;
		w->count.i3 = 0;
		w->params_vars.tmp = w->params_vars.tmp->next;
	}
	while (w->count.i3 <= w->params_vars.line_width + 1)
		w->map[w->count.i][w->count.i3++] = 1;
	}

	// Position