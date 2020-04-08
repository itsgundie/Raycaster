/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amargy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 19:05:00 by amargy            #+#    #+#             */
/*   Updated: 2019/04/27 21:56:08 by amargy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t h;
	size_t n;
	size_t l;

	h = 0;
	l = 0;
	if (!*needle)
		return ((char*)haystack);
	while (haystack[h] != '\0' && len > 0)
	{
		n = 0;
		l = len;
		if (haystack[h] == needle[n])
		{
			while (needle[n] != '\0' && haystack[h + n] == needle[n] && l-- > 0)
				n++;
			if (needle[n] == '\0')
				return ((char*)&haystack[h]);
		}
		h++;
		len--;
	}
	return (0);
}
