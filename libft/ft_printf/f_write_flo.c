/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_write_flo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edestiny <edestiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 22:43:18 by edestiny          #+#    #+#             */
/*   Updated: 2019/12/30 09:56:00 by edestiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	write_bef_dot_dub(t_bg *nd, char **pos)
{
	dubtoi(expa_choice(nd->n[nd->hi]), pos, nd->n[nd->hi & 127], 0);
	while (--(nd->hi) >= 0)
		dubtoi(8, pos, nd->n[nd->hi & 127], 0);
}

void	write_bef_long_dot(t_bgl *nd, char **pos)
{
	dubtoi(expa_choice(nd->n[nd->hi]), pos, nd->n[nd->hi & 2047], 0);
	while (--(nd->hi) >= 0)
		dubtoi(8, pos, nd->n[nd->hi & 2047], 0);
}

void	write_af_lo_dot(t_bgl *nd, char **pos, int pre, int zero)
{
	int prepos;

	prepos = pre % 9;
	while (nd->hi > nd->lo || (!prepos && nd->hi >= nd->lo))
	{
		dubtoi(8, pos, nd->n[nd->hi & 2047], 0);
		nd->hi--;
		zero -= 9;
	}
	if (prepos && -nd->lo * 9 >= pre)
	{
		dubtoi(8, pos, nd->n[nd->hi & 2047], 9 - prepos);
		zero -= (8 - (9 - (prepos + 1)));
	}
	while (zero > 0)
	{
		**pos = '0';
		(*pos)++;
		--zero;
	}
}

char	*long_2_str(t_bgl *nd, int pre, char *str, int zero)
{
	char	*pos;

	nd->sign ? (*str = '-') : 0;
	pos = (nd->sign) ? ++str : str;
	while (nd->hi && !nd->n[nd->hi])
		nd->hi--;
	write_bef_long_dot(nd, &pos);
	(pre) ? *pos++ = '.' : 0;
	write_af_lo_dot(nd, &pos, pre, zero);
	*pos = '\0';
	return (str);
}

void	write_af_dub_dot(t_bg *nd, char **pos, int pre, int zero)
{
	int prepos;

	prepos = pre % 9;
	while (nd->hi > nd->lo || (!prepos && nd->hi >= nd->lo))
	{
		dubtoi(8, pos, nd->n[nd->hi & 127], 0);
		nd->hi--;
		zero -= 9;
	}
	if (prepos && -nd->lo * 9 >= pre)
	{
		dubtoi(8, pos, nd->n[nd->hi & 127], 9 - prepos);
		zero -= (8 - (9 - (prepos + 1)));
	}
	while (zero > 0)
	{
		**pos = '0';
		(*pos)++;
		--zero;
	}
}
