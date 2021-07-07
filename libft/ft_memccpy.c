/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 20:18:46 by seuyu             #+#    #+#             */
/*   Updated: 2021/07/07 15:39:18 by seuyu            ###   ########.fr       */
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
