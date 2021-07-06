/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parse_size_utils.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 15:03:43 by sejpark           #+#    #+#             */
/*   Updated: 2021/07/06 15:11:40 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_PARSE_SIZE_UTILS_H
# define GET_PARSE_SIZE_UTILS_H
# include "../libft/libft.h"

extern int	g_exit_status;
int			env_value_size(char *str, int size, char **envp);
int			env_key_size(char *str);
int			env_cnt(char *str, int *size, char **envp);
int			d_quote_cnt(char *str, int *size, char **envp);
int			s_quote_cnt(char *str, int *size);

#endif
