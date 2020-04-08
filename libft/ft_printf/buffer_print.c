/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edestiny <edestiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 18:58:13 by amargy            #+#    #+#             */
/*   Updated: 2019/12/30 09:53:58 by edestiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	print_buff(t_printf *p)
{
	write(1, p->buff, p->i_buff);
	p->s += p->i_buff;
	p->i_buff = 0;
}

void	buffcpy(char *res, t_printf *p, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (p->i_buff >= BUFF_SIZE_PRINTF)
			print_buff(p);
		p->buff[p->i_buff] = res[i];
		i++;
		p->i_buff++;
	}
}

void	print_arg(char *res, t_printf *p)
{
	if (p->string_f || p->char_f)
	{
		buffcpy(res, p, p->i_res + 1);
		return ;
	}
	while (p->i_res >= 0)
	{
		if (p->i_buff >= BUFF_SIZE_PRINTF)
			print_buff(p);
		p->buff[p->i_buff] = res[p->i_res];
		p->i_buff++;
		p->i_res--;
	}
	if (!p->float_f)
		free(res);
	res = NULL;
}
