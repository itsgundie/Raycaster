/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amargy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:11:38 by amargy            #+#    #+#             */
/*   Updated: 2019/05/04 14:38:36 by amargy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	move(const char *str)
{
	int i;

	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\r' || str[i] == '\v'
	|| str[i] == '\f' || str[i] == ' ')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int			i;
	long long	at;
	int			neg;

	i = move(str);
	at = 0;
	neg = 1;
	if (str[i] == '-' && str[i + 1] >= 48 && str[i + 1] <= 57)
	{
		neg = -neg;
		i++;
	}
	if (str[i] == '+' && str[i + 1] >= 48 && str[i + 1] <= 57)
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		if (at * 10 + str[i] - 48 <= neg && neg == -1)
			return (0);
		if (at * 10 + str[i] - 48 != -1 && neg > 0 && at >= 922337203685477580)
			return (-1);
		at = at * 10 + str[i] - 48;
		i++;
	}
	return ((int)(at * neg));
}
