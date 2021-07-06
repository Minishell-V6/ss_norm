/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 21:42:57 by sejpark           #+#    #+#             */
/*   Updated: 2021/07/06 15:56:41 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/alloc_token.h"

void	ft_copy_str(char *src, char *dest, char **envp)
{
	int		src_idx;
	int		size;
	char	*dest_end;

	size = 0;
	src_idx = -1;
	dest_end = dest;
	while (src[++src_idx])
	{
		if (src[src_idx] == '\'' && unclosed_quote(&src[src_idx], '\''))
			src_idx += alloc_s_quote_cnt(&src[src_idx], &dest_end);
		else if (src[src_idx] == '\"' && unclosed_quote(&src[src_idx], '\"'))
			src_idx += alloc_d_quote_cnt(&src[src_idx], &dest_end, envp);
		else if (src[src_idx] == '$')
			src_idx += alloc_env(&src[src_idx], &dest_end, envp);
		else if (src[src_idx])
		{
			*dest_end = src[src_idx];
			dest_end++;
		}
	}
	*dest_end = '\0';
}

t_token	*ft_alloc_token(t_token *token, char **envp)
{
	int		cmd_len;
	size_t	i;
	char	*tmp_cmd;

	i = 0;
	while (token[i].cmd)
	{
		cmd_len = 0;
		tmp_cmd = token[i].cmd;
		cmd_len = get_parse_size(tmp_cmd, envp);
		if (token[i].cmd[0] == '<' || token[i].cmd[0] == '>')
		{
			if (redir_chk(token[i].cmd))
				token[i].redir_flag = 1;
			else
				token[i].redir_flag = -1;
		}
		token[i].cmd = (char*)malloc(sizeof(char) * (cmd_len + 1));
		ft_copy_str(tmp_cmd, token[i].cmd, envp);
		free(tmp_cmd);
		i++;
	}
	return (token);
}
