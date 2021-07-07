/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_chk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 16:00:44 by sejpark           #+#    #+#             */
/*   Updated: 2021/07/07 01:19:41 by seuyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/redir_chk.h"

int redir_chk(char *str)
{
	size_t str_len;

	str_len = ft_strlen(str);
	if (!ft_strncmp("<<", str, str_len) || !ft_strncmp(">>", str, str_len)
		|| !ft_strncmp("<", str, str_len) || !ft_strncmp(">", str, str_len))
		return (1);
	else
		return (0);
}

char *alloc_unexpected_token(char *redir)
{
	char *result;

	result = NULL;
	if (ft_strncmp(redir, "<<", 2) == 0)
	{
		if (ft_strncmp(redir + 2, "<<", 2) == 0
				|| ft_strncmp(redir + 2, ">>", 2) == 0)
			result = ft_substr(redir, 2, 2);
		else if (ft_strncmp(redir + 2, "<", 1) == 0
				|| ft_strncmp(redir + 2, ">", 1) == 0)
			result = ft_substr(redir, 2, 1);
	}
	else if (ft_strncmp(redir, ">>", 2) == 0)
	{
		if (ft_strncmp(redir + 2, "<<", 2) == 0
				|| ft_strncmp(redir + 2, ">>", 2) == 0)
			result = ft_substr(redir, 2, 2);
		else if (ft_strncmp(redir + 2, "<", 1) == 0
				|| ft_strncmp(redir + 2, ">", 1) == 0)
			result = ft_substr(redir, 2, 1);
	}
	else if (ft_strncmp(redir, "<", 1) == 0)
	{
		if (ft_strncmp(redir + 1, "<<", 2) == 0
				|| ft_strncmp(redir + 1, ">>", 2) == 0)
			result = ft_substr(redir, 1, 2);
		else if (ft_strncmp(redir + 1, "<", 1) == 0
				|| ft_strncmp(redir + 1, ">", 1) == 0)
			result = ft_substr(redir, 1, 1);
	}
	else if (ft_strncmp(redir, ">", 1) == 0)
	{
		if (ft_strncmp(redir + 1, "<<", 2) == 0
				|| ft_strncmp(redir + 1, ">>", 2) == 0)
			result = ft_substr(redir, 1, 2);
		else if (ft_strncmp(redir + 1, "<", 1) == 0
				|| ft_strncmp(redir + 1, ">", 1) == 0)
			result = ft_substr(redir, 1, 1);
	}
	return (result);
}

int redir_err_chk(t_cmd *cmd_list)
{
	int i;

	i = 0;
	while (cmd_list->cmdline[i].cmd)
	{
		if (cmd_list->cmdline[i].rd_flg == -1)
		{
			cmd_list->err.token = alloc_unexpected_token(cmd_list->cmdline[i].cmd);
			cmd_list->err.code = 7;
			return (-1);
		}
		i++;
	}
	return (1);
}
