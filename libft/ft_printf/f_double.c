/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_double.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edestiny <edestiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 15:15:03 by edestiny          #+#    #+#             */
/*   Updated: 2019/12/30 09:54:37 by edestiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*dub_2_str(t_bg *nd, int pre, char *str, int zero)
{
	char	*pos;

	nd->sign ? (*str = '-') : 0;
	pos = (nd->sign) ? ++str : str;
	if (nd->hi && !nd->n[nd->hi])
		nd->hi--;
	write_bef_dot_dub(nd, &pos);
	(pre) ? *pos++ = '.' : 0;
	write_af_dub_dot(nd, &pos, pre, zero);
	*pos = '\0';
	return (str);
}

char	*bad_num_dubl(t_val *tmp, char *dubstr, int sign)
{
	if (((tmp->u32.hi & 0x000fffff) | tmp->u32.lo) != 0)
		return (ft_strcpy(dubstr, "nan"));
	else
		return ((ft_strcpy(dubstr, (sign ? "-inf" : "inf"))));
}

void	get_dub_fracture(t_val *tmp, t_bg *nd, int32_t *expa)
{
	if (tmp->u32.lo)
	{
		*expa -= 32;
		nd->n[0] = nd->n[0] << 3 | tmp->u32.lo >> 29;
		mult_nd_dub(nd, 29, tmp->u32.lo & 0x1fffffff);
	}
}

void	implicit_bit(int32_t *expa, t_bg *nd)
{
	*expa == 0 ? ((*expa)++) : (nd->n[0] |= 0x100000);
}

char	*double_trouble(double *n, int pre, char *dubstr)
{
	t_val		tmp;
	int32_t		expa;
	t_bg		nd;
	int			repre;

	tmp.n = *n;
	nd.hi = 0;
	nd.lo = 0;
	repre = pre;
	nd.sign = (tmp.u32.hi >> 31);
	if ((tmp.u32.hi << 1) >= 0xffe00000)
		return (bad_num_dubl(&tmp, dubstr, nd.sign));
	else
	{
		expa = tmp.u32.hi >> 20 & 0x7ff;
		nd.n[0] = tmp.u32.hi & 0xfffff;
		implicit_bit(&expa, &nd);
		expa -= 1043;
		get_dub_fracture(&tmp, &nd, &expa);
		(expa >= 0) ? mult_nd_dub(&nd, (uint32_t)expa, 0)
						: div_nd_dub(&nd, (uint32_t)-expa);
		if (n && nd.lo)
			do_round_dub(&nd, &pre);
		return (dub_2_str(&nd, pre, dubstr, repre));
	}
}
