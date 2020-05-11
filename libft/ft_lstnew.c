/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amargy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 22:57:02 by amargy            #+#    #+#             */
/*   Updated: 2019/05/13 19:37:58 by amargy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *newlink;

	if (!(newlink = (t_list *)malloc(sizeof(t_list))))
		return (0);
	newlink->next = 0;
	if (!content)
	{
		newlink->content = 0;
		newlink->content_size = 0;
		return (newlink);
	}
	if (!(newlink->content = (void *)malloc(content_size)))
	{
		free(newlink);
		return (0);
	}
	ft_memcpy(newlink->content, content, content_size);
	newlink->content_size = content_size;
	return (newlink);
}
