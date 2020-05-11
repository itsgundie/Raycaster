/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edestiny <edestiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 19:38:09 by amargy            #+#    #+#             */
/*   Updated: 2019/12/30 09:59:09 by edestiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		ft_printf(const char *format, ...)
{
	static t_printf					p;
	static t_function_point_array	fpa[256];

	if (p.static_ft_printf == 0)
		spec_flags(fpa);
	p.format = (char *)format;
	va_start(p.ap, format);
	pars(&p, fpa);
	return (p.s);
}
