/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_long.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edestiny <edestiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 20:55:29 by edestiny          #+#    #+#             */
/*   Updated: 2019/12/30 09:55:14 by edestiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		expa_choice(unsigned int val)
{
	int expa;

	expa = 0;
	if (val >= 10000 && (val /= 10000))
		expa += 4;
	if (val >= 1000 && (val /= 1000))
		expa += 3;
	if (val >= 100 && (val /= 100))
		expa += 2;
	if (val >= 10 && (val /= 10))
		expa += 1;
	return (expa);
}

void	mult_nd_long(t_bgl *nd, uint32_t pos, uint32_t carry)
{
	uint32_t i;

	while (pos >= 29)
	{
		i = -1;
		mult_long_main(nd, &carry, &i);
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
		mult_long_last(nd, &carry, &i, pos);
		if (carry)
			nd->n[++(nd->hi)] = carry;
	}
}

char	*bad_num_long(t_val64 *tmp, char *dubstr, int sign)
{
	if ((tmp->u64.lo << 1) != 0)
		return (ft_strcpy(dubstr, "nan"));
	else
		return ((ft_strcpy(dubstr, (sign ? "-inf" : "inf"))));
}

void	get_long_fracture(t_val64 *tmp, t_bgl *nd, int32_t *expa)
{
	if (tmp->u64.lo & 0x3FFFFFFFFFFFFFF)
	{
		*expa -= 58;
		mult_nd_long(nd, 29, (tmp->u64.lo >> 29) & 0x1FFFFFFF);
		mult_nd_long(nd, 29, tmp->u64.lo & 0x1FFFFFFF);
	}
}

char	*long_double_trouble(long double *n, int pre, char *dubstr)
{
	t_val64		tmp;
	int32_t		expa;
	t_bgl		nd;
	int			repre;

	tmp.n = *n;
	nd.lo = 0;
	nd.hi = 0;
	repre = pre;
	nd.sign = tmp.u64.hi >> 15;
	if ((tmp.u64.hi << 49) >= 0xfffe000000000000)
		return (bad_num_long(&tmp, dubstr, nd.sign));
	else
	{
		expa = (tmp.u64.hi & 0x7fff);
		nd.n[0] = (tmp.u64.lo >> 58) & 0x3f;
		expa -= 16388;
		get_long_fracture(&tmp, &nd, &expa);
		if (expa >= 0)
			mult_nd_long(&nd, (uint32_t)expa, 0);
		else if (1)
			div_nd_long(&nd, (uint32_t)-expa);
		(*n && nd.lo) ? (do_long_round(&nd, &pre)) : 0;
		return (long_2_str(&nd, pre, dubstr, repre));
	}
}
