/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_ten_pow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edestiny <edestiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 23:36:40 by edestiny          #+#    #+#             */
/*   Updated: 2019/12/30 09:55:49 by edestiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

unsigned int		g_ten_pow[] =
{
	1,
	10,
	100,
	1000,
	10000,
	100000,
	1000000,
	10000000,
	100000000
};

void	div_nd_dub(t_bg *nd, uint32_t pos)
{
	uint32_t	carry;
	uint32_t	i;

	while (pos >= 9)
	{
		carry = 0;
		i = nd->hi & 127;
		div_dub_hi(nd, &carry, &i);
		if (carry)
			nd->n[--(nd->lo) & 127] = carry;
		pos -= 9;
	}
	if (pos)
	{
		carry = 0;
		i = nd->hi & 127;
		div_dub_last(nd, &carry, &i, pos);
		if (carry)
			nd->n[--(nd->lo) & 127] = carry;
	}
}

void	dubtoi(int up, char **pos, uint32_t u, int pre)
{
	while (up >= pre)
	{
		**pos = (u / g_ten_pow[up]) % 10 + 48U;
		(*pos)++;
		up--;
	}
}
