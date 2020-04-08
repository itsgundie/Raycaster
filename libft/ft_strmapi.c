/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amargy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 15:13:19 by amargy            #+#    #+#             */
/*   Updated: 2019/05/07 16:53:27 by amargy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*n;
	int		i;

	i = 0;
	if (!s || !(*s) || !f)
		return (NULL);
	if (!(n = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	while (s[i] != '\0')
	{
		n[i] = f(i, s[i]);
		i++;
	}
	n[i] = '\0';
	return (n);
}
