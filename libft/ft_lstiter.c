/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 16:04:19 by mac               #+#    #+#             */
/*   Updated: 2021/07/06 22:09:10 by seuyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*next;

	if (lst == NULL || f == NULL)
		return ;
	while (lst)
	{
		next = lst->next;
		f(lst->content);
		lst = next;
	}
}
