/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 21:36:03 by seuyu             #+#    #+#             */
/*   Updated: 2021/07/07 15:37:37 by seuyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstadd_back(t_list **lst, t_list *new1)
{
	t_list	*last;

	if (lst == NULL || new1 == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new1;
		return ;
	}
	last = ft_lstlast(*lst);
	new1->next = last->next;
	last->next = new1;
}
