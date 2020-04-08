/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amargy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 23:13:57 by amargy            #+#    #+#             */
/*   Updated: 2019/05/15 14:50:16 by amargy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst2;
	unsigned char	*src2;

	if (dst == 0 && src == 0)
		return (0);
	dst2 = (unsigned char*)dst;
	src2 = (unsigned char*)src;
	while (n-- > 0)
		*(dst2++) = *(src2++);
	return (dst);
}
