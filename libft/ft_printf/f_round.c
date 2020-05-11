/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_round.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edestiny <edestiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 22:35:18 by amargy            #+#    #+#             */
/*   Updated: 2019/12/30 09:55:39 by edestiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	round_up(uint32_t *nd, int nd_lo, int mask)
{
	while (nd[nd_lo & mask] >= 1000000000)
	{
		nd_lo++;
		nd[nd_lo & mask] += 1;
	}
}

void	round_lo(int pre, int prepos, int *ndlo)
{
	if (!pre)
		*ndlo = 0;
	else if (!prepos && -*ndlo * 9 >= pre)
		*ndlo = -pre / 9;
	else if (prepos && -*ndlo * 9 >= pre)
		*ndlo = -pre / 9 - 1;
}

int		round_tail(int nd_lo, int pre, uint32_t *nd, int mask)
{
	int	prep;
	int lo_tmp;

	lo_tmp = nd_lo;
	prep = (pre % 9);
	round_lo(pre, prep, &nd_lo);
	if (((pre / 9) + 1) == -lo_tmp &&
		!(nd[lo_tmp & mask] % g_ten_pow[8 - prep]))
	{
		if (prep && (nd[nd_lo & mask] / g_ten_pow[9 - prep] % 10) & 1
			&& (nd[nd_lo & mask] / g_ten_pow[8 - prep]) % 10 == 5)
			nd[nd_lo & mask] += g_ten_pow[9 - prep];
		else if (!prep && (lo_tmp <= nd_lo - 1) && (nd[nd_lo & mask] % 10) & 1
			&& nd[(nd_lo - 1) & mask] / g_ten_pow[8] == 5)
			nd[nd_lo & mask] += 1;
	}
	else
	{
		if (prep && (nd[nd_lo & mask] / g_ten_pow[8 - prep]) % 10 >= 5)
			nd[nd_lo & mask] += g_ten_pow[9 - prep];
		else if (!prep && (lo_tmp <= nd_lo - 1)
			&& nd[(nd_lo - 1) & mask] / g_ten_pow[8] >= 5)
			nd[nd_lo & mask] += 1;
	}
	return (nd_lo);
}

void	do_long_round(t_bgl *nd, int *pre)
{
	if (*pre > -nd->lo * 9)
		*pre = -nd->lo * 9;
	nd->lo = round_tail(nd->lo, *pre, nd->n, 2047);
	round_up(nd->n, nd->lo, 2047);
}

void	do_round_dub(t_bg *nd, int *pre)
{
	if (*pre > -nd->lo * 9)
		*pre = -nd->lo * 9;
	nd->lo = round_tail(nd->lo, *pre, nd->n, 127);
	round_up(nd->n, nd->lo, 127);
}
