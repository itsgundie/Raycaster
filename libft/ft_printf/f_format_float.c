/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_format_float.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edestiny <edestiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:21:19 by amargy            #+#    #+#             */
/*   Updated: 2019/12/30 09:55:01 by edestiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void			print_str_float(char *s, t_printf *p)
{
	int			i;
	char		res[16001];

	i = 0;
	check_point(&s, p);
	while (s[i] != '\0')
		i++;
	while (--i >= 0)
	{
		res[p->i_res] = s[i];
		p->i_res++;
	}
	p->i_res--;
	if (res[p->i_res] == 'n')
		p->nan_f = 1;
	if (res[p->i_res] == 'i' || res[p->i_res - 1] == 'i')
		p->inf_f = 1;
	preprint(res, p);
	free(s);
}

void			check_point(char **s, t_printf *p)
{
	char		*tmp;

	if (p->sharp == 1 && p->prec == 0 && **s != 'n' && **s != 'i'
		&& *(*s + 1) != 'i')
	{
		tmp = *s;
		*s = ft_strjoin(tmp, ".");
		free(tmp);
	}
}

void			print_float2(char *s, t_printf *p)
{
	int			i;
	char		res[16001];

	i = 0;
	check_point(&s, p);
	while (s[i] != '\0')
		i++;
	while (--i >= 0)
	{
		res[p->i_res] = s[i];
		p->i_res++;
	}
	p->i_res--;
	if (res[p->i_res] == 'n')
		p->nan_f = 1;
	if (res[p->i_res] == 'i' || res[p->i_res - 1] == 'i')
		p->inf_f = 1;
	preprint(res, p);
	free(s);
}

void			print_float(char *s, t_printf *p)
{
	if ((ft_isdigit(*s) == 0 && *s != '-') ||
			(ft_isdigit(*(s + 1)) == 0 && *s == '-'))
	{
		p->zero = 0;
		s[0] == 'n' ? p->plus_f = 0 : 0;
		s[0] == 'n' ? p->space_f = 0 : 0;
		print_str_float(s, p);
	}
	else
		print_float2(s, p);
}

void			format_float(t_printf *p)
{
	long double	n;
	double		f;
	char		*float2str;
	char		*long2str;

	p->float_f = 1;
	p->prec_f == 0 || p->prec > LON_LEN ? p->prec = DEF_PRE : 0;
	if (p->length_capital_l == 1)
	{
		n = va_arg(p->ap, long double);
		if (!(long2str = (char*)malloc(sizeof(char) * (LON_LEN))))
			exit(-1);
		long_double_trouble(&n, p->prec, long2str);
		print_float(long2str, p);
	}
	else
	{
		f = va_arg(p->ap, double);
		if (!(float2str = (char*)malloc(sizeof(char) * (DUB_LEN))))
			exit(-1);
		double_trouble(&f, p->prec, float2str);
		print_float(float2str, p);
	}
	p->spec_found = 1;
}
