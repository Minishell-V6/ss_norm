/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 21:49:59 by mac               #+#    #+#             */
/*   Updated: 2021/07/06 22:09:44 by seuyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*srcc;
	char	*dstc;
	size_t	i;

	i = 0;
	srcc = (char *)src;
	dstc = (char *)dst;
	if (!dst && !src)
		return (0);
	if (srcc < dstc)
		while (len > 0)
		{
			*(dstc + len - 1) = *(srcc + len - 1);
			len--;
		}
	else
		while (i < len)
		{
			*(dstc + i) = *(srcc + i);
			i++;
		}
	return (dst);
}
