/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 18:06:01 by djeon             #+#    #+#             */
/*   Updated: 2021/07/06 19:55:09 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int				non_builtin_exec(t_cmd *cmd_list, char *argv[], char **envp, char *path, int fds[])
{
	int			status;
	pid_t		pid;
	pid_t		wpid;
	int			i;

	i = 1;
	argv[0] = path;
	while (cmd_list->cmdline[i].cmd != NULL && cmd_list->cmdline[i].redir_flag == 0)
	{
		argv[i] = cmd_list->cmdline[i].cmd;
		i++;
	}
	argv[i] = NULL;
	if ((pid = fork()) < -1)
		return (-1);
	if (pid == 0)
	{
		if (cmd_list->pipe_flag == 1)
			dup2(fds[1], 1);
		if (execve(path, argv, envp) == -1)
			return (-1);
	}
	else if (pid != 0)
	{
		wpid = waitpid(pid, &status, 0);
		g_exit_status = status >> 8;
	}
	return (0);
}

int				non_builtin(t_cmd *cmd_list, char *argv[], char **envp, int fds[])
{
	struct stat	*buf;
	char		*env_path;
	char		**paths;
	char		*tmp;
	int			i;
	int			flag;

	i = -1;
	flag = 0;
	if (!(buf = (struct stat*)malloc(sizeof(struct stat))))
	{
		free(buf);
		return (0);
	}
	if (cmd_list->cmdline[0].cmd[0] != '\0' && stat(cmd_list->cmdline[0].cmd, buf) == 0)
	{
		if ((non_builtin_exec(cmd_list, argv, envp, cmd_list->cmdline[0].cmd, fds)) == -1)
		{
			free(buf);
			return (0);
		}
		flag = 1;
	}
	else
	{
		if ((env_path = get_env_value("PATH", envp)) == NULL)
		{
			free(buf);
			return (0);
		}
		if ((paths = ft_split(env_path, ':')) == NULL)
		{
			free(buf);
			return (0);
		}
		while (paths[++i] != NULL)
		{
			if ((tmp = strjoin_path(paths[i], cmd_list->cmdline[0].cmd)) == 0)
			{
				free(buf);
				return (0);
			}
			if (cmd_list->cmdline[0].cmd[0] != '\0' && stat(tmp, buf) == 0)
			{
				if (non_builtin_exec(cmd_list, argv, envp, tmp, fds) == -1)
				{
					free(buf);
					return (0);
				}
				flag = 1;
				free(tmp);
				break ;
			}
			free(tmp);
		}
		i = -1;
		while (paths[++i] != NULL)
			free(paths[i]);
		free(paths);
	}
	if (flag == 0)
	{
		free(buf);
		return (0);
	}
	free(buf);
	return (1);
}

//int				exec_function(t_cmd *cmd_list, char *argv[], char **envp[], int fds[])
//{
//	int			fd;
//	int			right_flag;
//
//	if (redir_err_chk(cmd_list) == -1)
//		return (-1);
//	if ((right_flag = redirect_check(cmd_list, &fds)) == -1)
//		return (-1);
//	if (cmd_list->pipe_flag == 1 && right_flag == 0)
//		fd = fds[1];
//	else
//		fd = 1;
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
//}

int				exec(t_cmd *cmd_list, char *argv[], char **envp[])
{
	int			fds[2];
	int			status;
	pid_t		pid;
	pid_t		wpid;
	int			tmp;

	pipe(fds);
	if ((tmp = exec_function(cmd_list, argv, envp, fds)) == -1)
		print_errstr(cmd_list);
	else if (tmp == 1)
		g_exit_status = 0;
	dup2(100, STDOUT);
	dup2(101, STDIN);
	if (cmd_list->pipe_flag == 1)
	{
		if ((pid = fork()) < 0)
		{
			cmd_list->err_manage.errcode = 1;
			print_errstr(cmd_list);
			return (g_exit_status);
		}
	}
	else
		return (g_exit_status);
	if (pid == 0)
	{
		dup2(fds[0], 0);
		close(fds[0]);
		close(fds[1]);
		g_exit_status = exec(cmd_list->next, argv, envp);
		exit(g_exit_status);
	}
	else
	{
		close(fds[1]);
		close(fds[0]);
		wpid = waitpid(pid, &status, 0);
		g_exit_status = status >> 8;
		return (g_exit_status);
	}
}
