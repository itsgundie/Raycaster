/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amargy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 23:15:17 by amargy            #+#    #+#             */
/*   Updated: 2019/04/27 22:33:27 by amargy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t len)
{
	unsigned char *s2;

	s2 = (unsigned char*)s;
	while (len > 0 && *s2 != (unsigned char)c)
	{
		s2++;
		len--;
	}
	if (len == 0)
		return (NULL);
	else
		return (s2);
}
