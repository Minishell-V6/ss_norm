/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 20:34:27 by sejpark           #+#    #+#             */
/*   Updated: 2021/07/06 20:35:29 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "struct.h"

int				check_whitespace(char *line);
char			*strjoin_path(char const *s1, char const *s2);
void			free_list(t_cmd *cmd_list);

#endif
