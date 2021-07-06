/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 13:26:35 by sejpark           #+#    #+#             */
/*   Updated: 2021/07/06 13:32:08 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd_split_utils.h"

void	ft_quote_chk(char const *s, int *quote)
{
	if (*s == '"' && (*quote == 0 || *quote == '"'))
	{
		if (*quote == '"')
			*quote = 0;
		else
			*quote = '"';
	}
	else if (*s == '\'' && (*quote == 0 || *quote == '\''))
	{
		if (*quote == '\'')
			*quote = 0;
		else
			*quote = '\'';
	}
}

void	ft_begin_chk(char const *s, int *begin, int *redir)
{
	if (*s != ' ')
		*begin = 1;
	if (*s == '<' || *s == '>')
		(*redir)++;
}

void	ft_inc_cnt(int *redir, int *cnt)
{
	if (*redir)
		*redir = 0;
	(*cnt)++;
}

int		ft_cal_wordend(char const *s, int *begin, int *quote, int *redir)
{
	int cnt;

	cnt = 0;
	if (*s == ' ' && *quote == 0)
	{
		ft_inc_cnt(redir, &cnt);
		*begin = 0;
	}
	else if ((*s == '>' || *s == '<') && *quote == 0)
	{
		if (*redir == 0 && *(s - 1) != ' ')
			cnt++;
		(*redir)++;
	}
	else if (*s != ' ' && *s != '\'' && !(*s == '>' || *s == '<')
				&& *quote == 0 && (*(s - 1) == '>' || *(s - 1) == '<'))
		ft_inc_cnt(redir, &cnt);
	else if (*s == '\'' && *quote == '\''
				&& (*(s - 1) == '>' || *(s - 1) == '<'))
		ft_inc_cnt(redir, &cnt);
	else if (*s == '"' && *quote == '"' && (*(s - 1) == '>' || *(s - 1) == '<'))
		ft_inc_cnt(redir, &cnt);
	return (cnt);
}

int		ft_cal_wordlen(char const *s, int *len, int *begin, int *quote)
{
	ft_quote_chk(s, quote);
	if (*begin == 0)
	{
		if (*s != ' ')
		{
			*begin = 1;
			(*len)++;
		}
	}
	else
	{
		if (*s == ' ' && *quote == 0)
			return (0);
		else if ((*s == '>' || *s == '<') && *quote == 0)
			return (0);
		else
			(*len)++;
	}
	return (1);
}
