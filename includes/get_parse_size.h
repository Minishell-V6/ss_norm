/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parse_size.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 17:26:20 by seuyu             #+#    #+#             */
/*   Updated: 2021/07/06 15:12:03 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_PARSE_SIZE_H
# define GET_PARSE_SIZE_H
# include "../libft/libft.h"
# include "get_parse_size_utils.h"

extern int	g_exit_status;
int			unclosed_quote(char *str, char quote);
int			get_parse_size(char *str, char **envp);

#endif
