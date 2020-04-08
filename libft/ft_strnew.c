/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amargy <amargy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 20:48:22 by amargy            #+#    #+#             */
/*   Updated: 2019/06/17 22:03:24 by amargy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *str;

	if (size + 1 == 0)
		return (0);
	if (!(str = (char*)malloc(sizeof(char) * size + 1)))
		return (NULL);
	ft_memset(str, '\0', size + 1);
	return (str);
}
