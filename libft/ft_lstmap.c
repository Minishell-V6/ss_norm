/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 16:31:21 by mac               #+#    #+#             */
/*   Updated: 2021/07/06 22:09:16 by seuyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_head;
	t_list	*new_next;
	t_list	*curr;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	if ((new_head = ft_lstnew(f(lst->content))) == NULL)
		return (NULL);
	curr = new_head;
	lst = lst->next;
	while (lst)
	{
		if ((new_next = ft_lstnew(f(lst->content))) == NULL)
		{
			ft_lstclear(&new_head, del);
			return (NULL);
		}
		curr->next = new_next;
		curr = new_next;
		lst = lst->next;
	}
	return (new_head);
}
