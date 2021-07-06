/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 16:36:51 by hoylee            #+#    #+#             */
/*   Updated: 2021/07/06 02:06:04 by seuyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redir_buf(t_cmd *cmd_list, int i, int n)
{
	cmd_list->rd_buf[n] = cmd_list->cmdline[i].cmd;
	cmd_list->rd_buf[n + 1] = cmd_list->cmdline[i + 1].cmd;
}

int		is_redir(char *cmd)
{
	if (ft_strncmp("<", cmd, 2) == 0)
		return (1);
	else if (ft_strncmp("<<", cmd, 3) == 0)
		return (2);
	else if (ft_strncmp(">", cmd, 2) == 0)
		return (3);
	else if (ft_strncmp(">>", cmd, 3) == 0)
		return (4);
	return (0);
}

int		fd_err_chk(t_cmd *cmd_list, int i, int redir)
{
	int fd;

	fd = 0;
	if (redir == 1)
		fd = open(cmd_list->cmdline[i + 1].cmd, O_WRONLY | O_APPEND, 0744);
	else if (redir == 3)
		fd = open(cmd_list->cmdline[i + 1].cmd, O_WRONLY | O_CREAT | O_TRUNC, 0744);
	else if (redir == 4)
		fd = open(cmd_list->cmdline[i + 1].cmd, O_WRONLY | O_CREAT | O_APPEND, 0744);
	if (fd <= 0)
	{
		cmd_list->err_manage.errcode = 3;
		cmd_list->err_manage.errindex = i + 1;
		return (-1);
	}
	close(fd);
	return (1);
}

int		rd_err_chk(t_cmd *cmd_list, int i, int redir, int *last_index)
{
	if (cmd_list->cmdline[i + 1].cmd == 0)
	{
		cmd_list->err_manage.errcode = 8;
		return (-1);
	}
	else if (cmd_list->cmdline[i + 1].redir_flag == 1)
	{
		cmd_list->err_manage.errcode = 7;
		cmd_list->err_manage.errindex = i + 1;
		return (-1);
	}
	if (redir <= 2)
	{
		last_index[0] = i + 1;
		redir_buf(cmd_list, i, 0);
	}
	else
	{
		last_index[1] = i + 1;
		redir_buf(cmd_list, i, 2);
	}
	return (0);
}

int		redirect_check(t_cmd *cmd_list, int **fds)
{
	int			i;
	int			last_index[2];
	int			redir;

	i = -1;
	while (++i < 4)
		cmd_list->rd_buf[i] = 0;
	i = 0;
	while (cmd_list->cmdline[i].cmd)
	{
		redir = is_redir(cmd_list->cmdline[i].cmd);
		if (redir != 0)
		{
			if (rd_err_chk(cmd_list, i, redir, last_index) == -1)
				return (-1);
			if (fd_err_chk(cmd_list, i, redir) == -1)
				return (-1);
		}
		i++;
	}
	if ((cmd_list->rd_buf[0] || cmd_list->rd_buf[2]))
		return (redirect(cmd_list, fds, last_index));
	return (0);
}
