/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 16:27:21 by sejpark           #+#    #+#             */
/*   Updated: 2021/07/07 01:13:49 by seuyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

int		n_opt_chk(char *cmd)
{
	int i;

	i = 1;
	if (ft_strncmp("-n", cmd, 2) != 0)
		return (0);
	while (cmd[++i])
	{
		if (cmd[i] != 'n')
			return (0);
	}
	return (1);
}

int		ft_echo(t_cmd *cmd_list, int fd)
{
	int flg;
	int i;
	int cnt;

	i = 1;
	flg = 0;
	cnt = 0;
	while (n_opt_chk(cmd_list->cmdline[i].cmd))
	{
		flg = 1;
		i++;
	}
	while (cmd_list->cmdline[i].cmd && cmd_list->cmdline[i].rd_flg == 0)
	{
		if (cnt != 0)
			write(fd, " ", 1);
		ft_putstr_fd(cmd_list->cmdline[i].cmd, fd);
		i++;
		cnt++;
	}
	if (flg == 0)
		write(fd, "\n", 1);
	return (1);
}
