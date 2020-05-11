/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_multf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edestiny <edestiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 22:29:28 by edestiny          #+#    #+#             */
/*   Updated: 2019/12/30 09:55:24 by edestiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	mult_dub_main(t_bg *nd, uint32_t *carry, uint32_t *i)
{
	uint64_t val;

	while (++(*i) <= (uint32_t)nd->hi)
	{
		val = ((uint64_t)nd->n[*i] << 29) | *carry;
		*carry = (uint32_t)(val / 1000000000);
		nd->n[*i] = (uint32_t)val - *carry * 1000000000;
	}
}

void	mult_long_main(t_bgl *nd, uint32_t *carry, uint32_t *i)
{
	uint64_t val;

	while (++(*i) <= (uint32_t)nd->hi)
	{
		val = ((uint64_t)nd->n[*i] << 29) | *carry;
		*carry = (uint32_t)(val / 1000000000);
		nd->n[*i] = (uint32_t)val - *carry * 1000000000;
	}
}

void	mult_dub_last(t_bg *nd, uint32_t *carry, uint32_t *i, uint32_t pos)
{
	uint64_t val;

	while (++(*i) <= (uint32_t)nd->hi)
	{
		val = ((uint64_t)nd->n[*i] << pos) | *carry;
		*carry = (uint32_t)(val / 1000000000);
		nd->n[*i] = (uint32_t)val - *carry * 1000000000;
	}
}

void	mult_long_last(t_bgl *nd, uint32_t *carry, uint32_t *i, uint32_t pos)
{
	uint64_t val;

	while (++(*i) <= (uint32_t)nd->hi)
	{
		val = ((uint64_t)nd->n[*i] << pos) | *carry;
		*carry = (uint32_t)(val / 1000000000);
		nd->n[*i] = (uint32_t)val - *carry * 1000000000;
	}
}

void	mult_nd_dub(t_bg *nd, uint32_t pos, uint32_t carry)
{
	uint32_t i;

	while (pos >= 29)
	{
		i = -1;
		mult_dub_main(nd, &carry, &i);
		if (carry)
		{
			nd->n[++(nd->hi)] = carry;
			carry = 0;
		}
		pos -= 29;
	}
	if (pos)
	{
		i = -1;
		mult_dub_last(nd, &carry, &i, pos);
		if (carry)
			nd->n[++(nd->hi)] = carry;
	}
}
