/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 16:37:25 by seuyu             #+#    #+#             */
/*   Updated: 2021/07/07 02:06:05 by seuyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

int			set_cd(t_cmd *cmd_list)
{
	char *tmp;

	if (cmd_list->cmdline[1].cmd == 0 || cmd_list->cmdline[1].rd_flg == 1)
	{
		chdir(getenv("HOME"));
		return (1);
	}
	if (cmd_list->cmdline[1].cmd[0] == 0)
		return (1);
	if (cmd_list->cmdline[1].cmd[0] == '~')
	{
		if (cmd_list->cmdline[1].cmd[1] == '/')
		{
			tmp = ft_substr(cmd_list->cmdline[1].cmd, 1, \
			ft_strlen(cmd_list->cmdline[1].cmd + 1));
			free(cmd_list->cmdline[1].cmd);
			cmd_list->cmdline[1].cmd = ft_strjoin(getenv("HOME"), tmp);
			free(tmp);
		}
		else if (cmd_list->cmdline[1].cmd[1] == 0)
		{
			chdir(getenv("HOME"));
			return (1);
		}
	}
	return (0);
}

int			ft_cd(t_cmd *cmd_list)
{
	int		i;
	char	*dir_buffer;

	i = 0;
	dir_buffer = getcwd(0, 0);
	if (set_cd(cmd_list) == 1)
	{
		free(dir_buffer);
		return (1);
	}
	if (chdir(cmd_list->cmdline[1].cmd) == -1)
	{
		chdir(dir_buffer);
		cmd_list->err.code = 3;
		cmd_list->err.idx = 1;
		free(dir_buffer);
		return (-1);
	}
	free(dir_buffer);
	return (1);
}
