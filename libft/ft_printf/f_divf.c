/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_divf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edestiny <edestiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 22:32:59 by edestiny          #+#    #+#             */
/*   Updated: 2019/12/30 09:54:21 by edestiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void		div_dub_hi(t_bg *nd, uint32_t *carry, uint32_t *i)
{
	uint32_t val;

	while (1)
	{
		val = nd->n[*i];
		nd->n[*i] = (val >> 9) + *carry;
		*carry = (val & 0x1ff) * 1953125;
		if (*i == (nd->lo & 127))
			break ;
		*i = (*i - 1) & 127;
	}
}

void		div_long_hi(t_bgl *nd, uint32_t *carry, uint32_t *i)
{
	uint32_t val;

	while (1)
	{
		val = nd->n[*i];
		nd->n[*i] = (val >> 9) + *carry;
		*carry = (val & 0x1ff) * 1953125;
		if (*i == (nd->lo & 2047))
			break ;
		*i = (*i - 1) & 2047;
	}
}

void		div_dub_last(t_bg *nd, uint32_t *carry, uint32_t *i, uint32_t pos)
{
	uint32_t val;
	uint32_t mask;
	uint32_t mul;

	mask = (1U << pos) - 1;
	mul = 1000000000 >> pos;
	while (1)
	{
		val = nd->n[*i];
		nd->n[*i] = (val >> pos) + *carry;
		*carry = (val & mask) * mul;
		if (*i == (nd->lo & 127))
			break ;
		*i = (*i - 1) & 127;
	}
}

void		div_long_last(t_bgl *nd, uint32_t *carry, uint32_t *i, uint32_t pos)
{
	uint32_t val;
	uint32_t mask;
	uint32_t mul;

	mask = (1U << pos) - 1;
	mul = 1000000000 >> pos;
	while (1)
	{
		val = nd->n[*i];
		nd->n[*i] = (val >> pos) + *carry;
		*carry = (val & mask) * mul;
		if (*i == (nd->lo & 2047))
			break ;
		*i = (*i - 1) & 2047;
	}
}

void		div_nd_long(t_bgl *nd, uint32_t pos)
{
	uint32_t carry;
	uint32_t i;

	while (pos >= 9)
	{
		carry = 0;
		i = nd->hi & 2047;
		div_long_hi(nd, &carry, &i);
		if (carry)
			nd->n[--(nd->lo) & 2047] = carry;
		pos -= 9;
	}
	if (pos)
	{
		carry = 0;
		i = nd->hi & 2047;
		div_long_last(nd, &carry, &i, pos);
		if (carry)
			nd->n[--(nd->lo) & 2047] = carry;
	}
}
