/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 20:18:46 by mac               #+#    #+#             */
/*   Updated: 2021/07/06 22:09:29 by seuyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char	*result;
	char	*start;
	char	tmp;

	result = (char*)dst;
	start = (char*)src;
	tmp = (unsigned char)c;
	if (!dst && !src)
		return (0);
	while (n--)
	{
		*result++ = *start;
		if (*start++ == tmp)
			return (result);
	}
	return (0);
}
