/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 16:51:04 by seuyu             #+#    #+#             */
/*   Updated: 2021/07/07 15:39:18 by seuyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*tmp;
	unsigned char	tmp2;

	tmp = (unsigned char*)s;
	tmp2 = (unsigned char)c;
	while (n--)
	{
		if (*tmp++ == tmp2)
		{
			tmp -= 1;
			return ((void*)tmp);
		}
	}
	return (0);
}
