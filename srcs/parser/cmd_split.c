/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 15:33:09 by sejpark           #+#    #+#             */
/*   Updated: 2021/07/06 14:08:17 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd_split.h"

static int	ft_split_cnt(char const *s)
{
	int cnt;
	int begin;
	int quote;
	int redir;

	cnt = 0;
	begin = 0;
	quote = 0;
	redir = 0;
	while (*s)
	{
		ft_quote_chk(s, &quote);
		if (begin == 0)
			ft_begin_chk(s, &begin, &redir);
		else
			cnt += ft_cal_wordend(s, &begin, &quote, &redir);
		s++;
	}
	return (begin == 0 ? cnt : cnt + 1);
}

static int	ft_word_len(char const *s)
{
	int len;
	int begin;
	int quote;

	len = 0;
	begin = 0;
	quote = 0;
	if (*s == '>' || *s == '<')
	{
		while (*s)
		{
			if (*s == '>' || *s == '<')
				len++;
			else
				return (len);
			s++;
		}
	}
	while (*s)
	{
		if (ft_cal_wordlen(s, &len, &begin, &quote) == 0)
			break ;
		s++;
	}
	return (len);
}

static char	*ft_alloc_word(int *idx, char const *s)
{
	int		word_len;
	char	*word;
	int		i;

	word_len = ft_word_len(&s[*idx]);
	word = (char*)malloc(sizeof(char) + (word_len + 1));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (i < word_len)
	{
		word[i] = s[*idx + i];
		i++;
	}
	word[i] = '\0';
	*idx += word_len;
	return (word);
}

static void	*ft_free(t_token *result, int len)
{
	int i;

	i = 0;
	while (i < len)
		free(result[i++].cmd);
	return (NULL);
}

t_token		*cmd_split(char const *s)
{
	int		i;
	int		cursor;
	t_token	*result;

	if (s == NULL)
		return (NULL);
	i = 0;
	cursor = 0;
	result = (t_token*)malloc(sizeof(t_token) * (ft_split_cnt(s) + 1));
	if (result == NULL)
		return (NULL);
	while (s[cursor])
	{
		if (s[cursor] == ' ')
			cursor++;
		else
		{
			result[i].cmd = ft_alloc_word(&cursor, s);
			result[i].redir_flag = 0;
			if (result[i++].cmd == NULL)
				return (ft_free(result, i));
		}
	}
	result[i].cmd = 0;
	return (result);
}
