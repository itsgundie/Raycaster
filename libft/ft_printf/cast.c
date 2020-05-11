/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amargy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 19:05:27 by amargy            #+#    #+#             */
/*   Updated: 2019/12/28 19:06:46 by amargy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	cast_signed(t_printf *p)
{
	if (p->mod[0] == 0 && p->base != 8)
		p->arg = (int)p->arg;
	else if (p->mod[0] == 'l' && p->mod[1] != 'l' && p->base != 8)
		p->arg = (long)p->arg;
	else if ((p->mod[0] == 'l' && p->mod[1] == 'l') || p->base == 8)
		p->arg = (long long)p->arg;
	else if (p->mod[0] == 'h' && p->mod[1] != 'h')
		p->arg = (short)p->arg;
	else if (p->mod[0] == 'h' && p->mod[1] == 'h')
		p->arg = (signed char)p->arg;
}

void	cast_unsigned(t_printf *p)
{
	if (p->mod[0] == 0)
		p->arg = (unsigned int)p->arg;
	else if (p->mod[0] == 'l' && p->mod[1] != 'l')
		p->arg = (unsigned long)p->arg;
	else if (p->mod[0] == 'l' && p->mod[1] == 'l')
		p->arg = (unsigned long long)p->arg;
	else if (p->mod[0] == 'h' && p->mod[1] != 'h')
		p->arg = (unsigned short)p->arg;
	else if (p->mod[0] == 'h' && p->mod[1] == 'h')
		p->arg = (unsigned char)p->arg;
}

void	cast_arg(t_printf *p)
{
	if (p->unsign == 0 && p->base == 10)
		cast_signed(p);
	else
		cast_unsigned(p);
}
