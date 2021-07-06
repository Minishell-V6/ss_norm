/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 15:07:11 by mac               #+#    #+#             */
/*   Updated: 2021/07/06 22:09:42 by seuyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*result;
	char	*start;

	result = (char*)dst;
	start = (char*)src;
	if (!dst && !src)
		return (0);
	while (n--)
	{
		*result++ = *start++;
	}
	return (dst);
}
