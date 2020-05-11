/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amargy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 02:00:32 by amargy            #+#    #+#             */
/*   Updated: 2019/05/07 17:06:20 by amargy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_whsp(char const *s, int *start, int *end)
{
	int		whsp;

	whsp = 0;
	while (s[*start] == ' ' || s[*start] == '\n' || s[*start] == '\t')
	{
		*start = *start + 1;
		whsp++;
	}
	if (s[*start] == '\0')
		return (whsp);
	while (s[*end] != '\0')
	{
		*end = *end + 1;
	}
	*end = *end - 1;
	while (s[*end] == ' ' || s[*end] == '\n' || s[*end] == '\t')
	{
		*end = *end - 1;
		whsp++;
	}
	return (whsp);
}

char			*ft_strtrim(char const *s)
{
	char	*cpy;
	int		start;
	int		end;
	int		whsp;
	int		start2;

	start = 0;
	start2 = 0;
	end = 0;
	if (!(s))
		return (NULL);
	whsp = ft_whsp(s, &start, &end);
	if (!(cpy = ft_strnew(ft_strlen(s) - whsp)))
		return (NULL);
	while (start <= end)
	{
		cpy[start2] = s[start];
		start2++;
		start++;
	}
	if (end < start)
		end++;
	cpy[end] = '\0';
	return (cpy);
}
