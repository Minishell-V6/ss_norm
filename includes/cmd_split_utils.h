/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 13:29:44 by sejpark           #+#    #+#             */
/*   Updated: 2021/07/06 22:06:36 by seuyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_SPLIT_UTILS_H
# define CMD_SPLIT_UTILS_H

void	ft_quote_chk(char const *s, int *quote);
void	ft_begin_chk(char const *s, int *begin, int *redir);
void	ft_inc_cnt(int *redir, int *cnt);
int		ft_cal_wordend(char const *s, int *begin, int *quote, int *redir);
int		ft_cal_wordlen(char const *s, int *len, int *begin, int *quote);
#endif
