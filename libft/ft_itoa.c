/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amargy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 18:04:50 by amargy            #+#    #+#             */
/*   Updated: 2019/05/08 17:32:24 by amargy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_digitsum(int *n, int *digitsum, int *digitoper)
{
	char *str;

	while (*digitoper != 0)
	{
		*digitoper = *digitoper / 10;
		*digitsum = *digitsum + 1;
	}
	if (*n < 0 || *n == 0)
		*digitsum = *digitsum + 1;
	if (!(str = (char *)malloc(sizeof(char) * (*digitsum + 1))))
		return (0);
	if (*n < 0)
	{
		str[0] = '-';
	}
	str[*digitsum] = '\0';
	if (*n == 0)
		str[*digitsum - 1] = 48;
	return (str);
}

char			*ft_itoa(int n)
{
	char	*str;
	int		digitsum;
	int		digitoper;

	digitsum = 0;
	digitoper = n;
	if (!(str = ft_digitsum(&n, &digitsum, &digitoper)))
		return (0);
	while (n != 0)
	{
		digitoper = n % 10;
		if (digitoper < 0)
			digitoper *= -1;
		str[--digitsum] = digitoper + 48;
		n /= 10;
	}
	return (str);
}
