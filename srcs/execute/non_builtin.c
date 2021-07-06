/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 20:22:05 by sejpark           #+#    #+#             */
/*   Updated: 2021/07/06 20:35:35 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/non_builtin.h"

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
