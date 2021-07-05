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

int					check_fd_error(t_cmd *cmd_list, int errorcode, int error_index, int fd)
{
	if (fd <= 0)
	{
		cmd_list->err_manage.errcode = errorcode;
		cmd_list->err_manage.errindex = error_index;
		return (-1);
	}
	return (0);
}
void	save_filename(t_cmd *cmd_list, int i, int first, int second)
{
	cmd_list->redirect_filename[first] = cmd_list->cmdline[i].cmd;
	cmd_list->redirect_filename[second] = cmd_list->cmdline[i + 1].cmd;
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

int				fd_err_chk(t_cmd *cmd_list, int i, int redir)
{
	int fd;

	if (redir == 1)
		fd = open(cmd_list->cmdline[i + 1].cmd, O_WRONLY | O_APPEND, 0744);
	if(redir == 3)
		fd = open(cmd_list->cmdline[i + 1].cmd, O_WRONLY | O_CREAT | O_TRUNC, 0744);
	else if(redir == 4)
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

int				rd_err_chk(t_cmd *cmd_list, int i, int redir, int *last_index)
{
	if(cmd_list->cmdline[i + 1].cmd == 0)
	{
		cmd_list->err_manage.errcode = 8;
		return (-1);
	}
	else if(cmd_list->cmdline[i + 1].redir_flag == 1)
	{
		cmd_list->err_manage.errcode = 7;
		cmd_list->err_manage.errindex = i + 1;
		return (-1);
	}
	if (redir <= 2)
	{
		save_filename(cmd_list, i, 0, 1);
		last_index[0] = i + 1;
	}
	else
	{
		save_filename(cmd_list, i, 2, 3);
		last_index[1] = i + 1;
	}
	return (0);
}
int				redirect_check(t_cmd *cmd_list, int **fds)
{
	int			i;
	int			last_index[2];
	int			redir;

	i = -1;
	while (++i < 4)
		cmd_list->redirect_filename[i] = 0;
	i = 0;
	while (cmd_list->cmdline[i].cmd)
	{
		redir = is_redir(cmd_list->cmdline[i].cmd);
		if (redir != 0) // 0 < redir && redir < 2
		{
			if (rd_err_chk(cmd_list, i, redir, last_index) == -1)
				return (-1);
			if (fd_err_chk(cmd_list, i, redir) == -1)
				return (-1);
		}
		i++;
	}
	if((cmd_list->redirect_filename[0] || cmd_list->redirect_filename[2]) ? 1 : 0)
		return (redirect(cmd_list, fds, last_index));
	else
		return (0);
}

// int				redirect_check(t_cmd *cmd_list, int **fds)
// {
// 	//여기서 리다이렉션 있는지 확인하고 해당 파일이 정상적인지 테스트함.
// 	int			i;
// 	int			fd;
// 	int			last_index[2];
// 	i = -1;
// 	while (++i < 4)
// 		cmd_list->redirect_filename[i] = 0;
// 	i = 0;
// 	while (cmd_list->cmdline[i].cmd)
// 	{
// 		if (cmd_list->cmdline[i].redir_flag == 0)
// 			;
// 		else if (ft_strncmp("<", cmd_list->cmdline[i].cmd, 2) == 0
// 							|| ft_strncmp("<<", cmd_list->cmdline[i].cmd, 3) == 0)
// 		{
// 			if(cmd_list->cmdline[i + 1].cmd == 0)
// 			{
// 				cmd_list->err_manage.errcode = 8;
// 				return (-1);
// 			}
// 			else if(cmd_list->cmdline[i + 1].redir_flag == 1)
// 			{
// 				cmd_list->err_manage.errcode = 7;
// 				cmd_list->err_manage.errindex = i + 1;
// 				return (-1);
// 			}
// 			save_filename(cmd_list, i, 0, 1);
// 			last_index[0] = i + 1;
// 			if (ft_strncmp("<", cmd_list->cmdline[i].cmd, 2) == 0)
// 			{
// 				fd = open(cmd_list->cmdline[i + 1].cmd, O_WRONLY | O_APPEND, 0744);
// 				if(check_fd_error(cmd_list, 3, i + 1, fd) == -1)
// 					return (-1);
// 				close(fd);
// 			}
// 		}
// 		else if (ft_strncmp(">", cmd_list->cmdline[i].cmd, 2) == 0
// 							|| ft_strncmp(">>", cmd_list->cmdline[i].cmd, 3) == 0)
// 		{
// 			if(cmd_list->cmdline[i + 1].cmd == 0)
// 			{
// 				cmd_list->err_manage.errcode = 8;
// 				return (-1);
// 			}
// 			else if(cmd_list->cmdline[i + 1].redir_flag == 1)
// 			{
// 				cmd_list->err_manage.errcode = 7;
// 				cmd_list->err_manage.errindex = i + 1;
// 				return (-1);
// 			}
// 			save_filename(cmd_list, i, 2, 3);
// 			last_index[1] = i + 1;
// 			if(ft_strncmp(">", cmd_list->cmdline[i].cmd, 2) == 0)
// 				fd = open(cmd_list->cmdline[i + 1].cmd, O_WRONLY | O_CREAT | O_TRUNC, 0744);
// 			else if(ft_strncmp(">>", cmd_list->cmdline[i].cmd, 3) == 0)
// 				fd = open(cmd_list->cmdline[i + 1].cmd, O_WRONLY | O_CREAT | O_APPEND, 0744);
// 			if(check_fd_error(cmd_list, 3, i + 1, fd) == -1)
// 				return (-1);
// 			close(fd);
// 		}
// 		i++;
// 	}
// 	if((cmd_list->redirect_filename[0] || cmd_list->redirect_filename[2]) ? 1 : 0)
// 		return (redirect(cmd_list, fds, last_index));
// 	else
// 		return (0);
// }
