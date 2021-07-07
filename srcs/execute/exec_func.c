/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 19:54:21 by sejpark           #+#    #+#             */
/*   Updated: 2021/07/07 01:12:36 by seuyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec_func.h"

int		call_function(t_cmd *cmd_list, int fd, char **envp[], char *argv[], int fds[])
{
	if (ft_strncmp("pwd", cmd_list->cmdline[0].cmd, 4) == 0)
		return (ft_pwd(fd));
	else if (ft_strncmp("cd", cmd_list->cmdline[0].cmd, 3) == 0)
		return (ft_cd(cmd_list));
	else if (ft_strncmp("exit", cmd_list->cmdline[0].cmd, 5) == 0)
		return (ft_exit(cmd_list));
	else if (ft_strncmp("env", cmd_list->cmdline[0].cmd, 4) == 0)
		return (ft_env(*envp, fd));
	else if (ft_strncmp("export", cmd_list->cmdline[0].cmd, 7) == 0)
		return (ft_export(cmd_list, envp, fd));
	else if (ft_strncmp("echo", cmd_list->cmdline[0].cmd, 5) == 0)
		return (ft_echo(cmd_list, fd));
	else if (ft_strncmp("unset", cmd_list->cmdline[0].cmd, 6) == 0)
		return (ft_unset(cmd_list, *envp));
	else if (non_builtin(cmd_list, argv, *envp, fds) == 0)
	{
		cmd_list->err.code = 1;
		return (-1);
	}
	return (0);
}

int		exec_function(t_cmd *cmd_list, char *argv[], char **envp[], int fds[])
{
	int			fd;
	int			right_flag;

	if (redir_err_chk(cmd_list) == -1)
		return (-1);
	if ((right_flag = redirect_check(cmd_list, &fds)) == -1)
		return (-1);
	if (cmd_list->pipe_flag == 1 && right_flag == 0)
		fd = fds[1];
	else
		fd = 1;
	return (call_function(cmd_list, fd, envp, argv, fds));
//	if (ft_strncmp("pwd", cmd_list->cmdline[0].cmd, 4) == 0)
//		return (ft_pwd(fd));
//	else if (ft_strncmp("cd", cmd_list->cmdline[0].cmd, 3) == 0)
//		return (ft_cd(cmd_list));
//	else if (ft_strncmp("exit", cmd_list->cmdline[0].cmd, 5) == 0)
//		return (ft_exit(cmd_list));
//	else if (ft_strncmp("env", cmd_list->cmdline[0].cmd, 4) == 0)
//		return (ft_env(*envp, fd));
//	else if (ft_strncmp("export", cmd_list->cmdline[0].cmd, 7) == 0)
//		return (ft_export(cmd_list, envp, fd));
//	else if (ft_strncmp("echo", cmd_list->cmdline[0].cmd, 5) == 0)
//		return (ft_echo(cmd_list, fd));
//	else if (ft_strncmp("unset", cmd_list->cmdline[0].cmd, 6) == 0)
//		return (ft_unset(cmd_list, *envp));
//	else if (non_builtin(cmd_list, argv, *envp, fds) == 0)
//	{
//		cmd_list->err_manage.errcode = 1;
//		return (-1);
//	}
//	return (0);
}
