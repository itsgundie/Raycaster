/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amargy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 23:14:21 by amargy            #+#    #+#             */
/*   Updated: 2019/04/27 01:25:01 by amargy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*dst2;
	unsigned char	*src2;

	dst2 = (unsigned char*)dst;
	src2 = (unsigned char*)src;
	i = 0;
	while (i < n)
	{
		dst2[i] = src2[i];
		if (dst2[i] == (unsigned char)c)
			return ((void*)(dst + i + 1));
		++i;
	}
	return (NULL);
}
