/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoylee <hoylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 16:36:03 by hoylee            #+#    #+#             */
/*   Updated: 2021/07/02 15:15:23 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				left_redirect(t_cmd *cmd_list, int *last_index)
{
	int			fd;

	fd = open(cmd_list->cmdline[last_index[0]].cmd, O_RDONLY, 0644);
	if (fd <= 0)
	{
		cmd_list->err_manage.errcode = 3;
		cmd_list->err_manage.errindex = last_index[0];
		return (-1);
	}
	dup2(fd, STDIN);
	close(fd);
	return (0);
}

int				left_redirect_double(t_cmd *cmd_list, int **fds)
{
	char		*line;

	while (ft_strncmp((line = readline("> ")), cmd_list->redirect_filename[1], 5))
		ft_putendl_fd(line, (*fds)[1]);
	close((*fds)[1]);
	dup2((*fds)[0], 0);
	close((*fds)[0]);
	pipe((*fds));
	return (0);
}

int				right_redirect(t_cmd *cmd_list, int *last_index)
{
	int			fd;

	fd = open(cmd_list->cmdline[last_index[1]].cmd, O_WRONLY | O_CREAT | O_TRUNC, 0744);
	if (fd <= 0)
	{
		cmd_list->err_manage.errcode = 3;
		cmd_list->err_manage.errindex = last_index[1];
		return (-1);
	}
	dup2(fd, STDOUT);
	close(fd);
	return (1);
}


int				right_redirect_double(t_cmd *cmd_list, int *last_index)
{
	int			fd;

	fd = open(cmd_list->cmdline[last_index[1]].cmd, O_WRONLY | O_CREAT | O_APPEND, 0744);
	if (fd <= 0)
	{
		cmd_list->err_manage.errcode = 3;
		cmd_list->err_manage.errindex = last_index[1];
		return (-1);
	}
	dup2(fd, STDOUT);
	close(fd);
	return (1);
}



int		redirect(t_cmd *cmd_list, int **fds, int *last_index)
{
	int error_left;
	int error_right;

	error_left = 0;
	error_right = 0;
	if (ft_strncmp("<", cmd_list->redirect_filename[0], 2) == 0)
		error_left = left_redirect(cmd_list, last_index);
	else if (ft_strncmp("<<", cmd_list->redirect_filename[0], 3) == 0)
		error_left = left_redirect_double(cmd_list, fds);
	if (ft_strncmp(">", cmd_list->redirect_filename[2], 2) == 0)
		error_right = right_redirect(cmd_list, last_index);
	else if (ft_strncmp(">>", cmd_list->redirect_filename[2], 3) == 0)
		error_right = right_redirect_double(cmd_list, last_index);
	if (error_left == -1 || error_right == -1)
		return -1;
	if (error_right == 1)
		return 1;
	return 0;
}

