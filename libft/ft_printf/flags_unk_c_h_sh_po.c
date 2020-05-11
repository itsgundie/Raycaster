/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_unk_c_h_sh_po.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edestiny <edestiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 09:56:23 by edestiny          #+#    #+#             */
/*   Updated: 2019/12/30 09:56:25 by edestiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	unknownspec(t_printf *p)
{
	if (p->i_buff >= BUFF_SIZE_PRINTF)
		print_buff(p);
	p->buff[p->i_buff] = p->format[p->i];
	p->i_buff++;
}

void	char_f(t_printf *p)
{
	char	res[2];

	p->char_f = 1;
	res[0] = va_arg(p->ap, int);
	if (res[0] == 0)
	{
		p->i_res = 0;
		preprint("\0", p);
		p->spec_found = 1;
		return ;
	}
	preprint(res, p);
	p->spec_found = 1;
}

void	short_f(t_printf *p)
{
	if (p->format[p->i + 1] == 'h')
	{
		p->mod[0] = 'h';
		p->mod[1] = 'h';
		p->i++;
	}
	else
		p->mod[0] = 'h';
}

void	sharp_f(t_printf *p)
{
	p->sharp = 1;
}

void	point_f(t_printf *p)
{
	p->prec_f = 1;
	p->i++;
	p->prec = atoi_width_prec(p);
}
