/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 23:09:16 by mac               #+#    #+#             */
/*   Updated: 2021/07/06 22:10:08 by seuyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strchr(const char *s, int c)
{
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (s[len] != '\0')
		len++;
	while (i != len && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return ((char*)&s[i]);
	return (0);
}
