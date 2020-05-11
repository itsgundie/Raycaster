/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amargy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 12:09:59 by amargy            #+#    #+#             */
/*   Updated: 2019/05/07 17:10:02 by amargy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_free(char **array, int arrstrindex)
{
	arrstrindex--;
	while (arrstrindex >= 0)
	{
		free(array[arrstrindex]);
		arrstrindex--;
	}
	array = NULL;
}

static char		**ft_stringsum(char const *s, char c, int stringsum)
{
	char	**array;
	int		index;

	index = 0;
	while (s[index] != '\0')
	{
		if (s[index] != c)
		{
			stringsum++;
			while (s[index] != c && s[index] != '\0')
				index++;
		}
		if (s[index] != '\0')
			index++;
	}
	array = (char **)malloc(sizeof(char *) * (stringsum + 1));
	if (!array)
		return (NULL);
	array[stringsum] = 0;
	return (array);
}

static char		**ft_stradd(char const *s, char c, char **array, int startstr)
{
	int		index;
	int		strlen;
	int		arrstrindex;

	index = 0;
	arrstrindex = 0;
	while (s[index] != '\0')
	{
		if (s[index] != c && s[index] != '\0')
		{
			strlen = 0;
			startstr = index;
			while (s[index] != c && s[index] != '\0')
			{
				index++;
				strlen++;
			}
			if (!(array[arrstrindex] = ft_strsub(s, startstr, strlen)))
				ft_free(array, arrstrindex);
			arrstrindex++;
		}
		if (s[index] != '\0')
			index++;
	}
	return (array);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**array;
	int		startstr;
	int		stringsum;

	startstr = 0;
	stringsum = 0;
	if (!s || !c)
		return (0);
	if (!(array = ft_stringsum(s, c, stringsum)))
		return (0);
	if (!(ft_stradd(s, c, array, startstr)))
		return (0);
	return (array);
}
