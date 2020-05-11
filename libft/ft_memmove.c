/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amargy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 23:14:58 by amargy            #+#    #+#             */
/*   Updated: 2019/05/15 14:54:30 by amargy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*dst2;
	unsigned char	*src2;

	if (dst == 0 && src == 0)
		return (0);
	dst2 = (unsigned char*)dst;
	src2 = (unsigned char*)src;
	i = 0;
	if (src2 < dst2)
		while (++i <= len)
			dst2[len - i] = src2[len - i];
	else
		while (len-- > 0)
			*(dst2++) = *(src2++);
	return (dst);
}
