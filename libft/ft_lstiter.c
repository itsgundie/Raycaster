/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amargy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 22:48:01 by amargy            #+#    #+#             */
/*   Updated: 2019/05/15 00:00:40 by amargy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	t_list *temp;
	t_list *temp2;

	if (lst && f)
	{
		temp = lst->next;
		while (temp != 0)
		{
			temp2 = temp->next;
			f(temp);
			temp = temp2;
		}
		f(lst);
	}
}
