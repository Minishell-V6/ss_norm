/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_token_utils.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 15:21:03 by sejpark           #+#    #+#             */
/*   Updated: 2021/07/06 15:57:43 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOC_TOKEN_UTILS_H
# define ALLOC_TOKEN_UTILS_H
# include "cmd_split.h"
# include "get_parse_size.h"
# include "ft_getenv.h"
# include "redir_chk.h"

extern int	g_exit_status;
int			get_envkey(char *src, char **key);
int			env_endchk(char *src, char **dest);
int			alloc_env(char *src, char **dest, char **envp);
int			alloc_d_quote_cnt(char *src, char **dest, char **envp);
int			alloc_s_quote_cnt(char *src, char **dest);

#endif
