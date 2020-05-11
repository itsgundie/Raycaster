/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amargy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 18:28:04 by amargy            #+#    #+#             */
/*   Updated: 2019/05/07 16:55:39 by amargy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*n;
	int		i;

	i = 0;
	if (!s || !(*s))
		return (NULL);
	if ((ft_strlen(s) + 1) < (start + len))
		return (NULL);
	if (!(n = ft_strnew(len)))
		return (NULL);
	while (len-- > 0)
	{
		n[i] = s[start];
		i++;
		start++;
	}
	n[i] = '\0';
	return (n);
}
