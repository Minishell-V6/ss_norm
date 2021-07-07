/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 20:22:05 by sejpark           #+#    #+#             */
/*   Updated: 2021/07/07 10:55:36 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/non_builtin.h"

void		set_argv(t_cmd *cmd_list, t_ae *t_ae_data, char *path, int *i)
{
	*i = 1;
	t_ae_data->argv[0] = path;
	while (cmd_list->cmdline[*i].cmd != NULL
				&& cmd_list->cmdline[*i].redir_flag == 0)
	{
		t_ae_data->argv[*i] = cmd_list->cmdline[*i].cmd;
		(*i)++;
	}
	t_ae_data->argv[*i] = NULL;
}

int			non_builtin_exec(t_cmd *cmd_list, t_ae t_ae_data, char *path,
								int fds[])
{
	int			status;
	pid_t		pid;
	pid_t		wpid;
	int			i;

	set_argv(cmd_list, &t_ae_data, path, &i);
	if ((pid = fork()) < -1)
		return (-1);
	if (pid == 0)
	{
		if (cmd_list->pipe_flag == 1)
			dup2(fds[1], 1);
		if (execve(path, t_ae_data.argv, t_ae_data.envp) == -1)
			return (-1);
	}
	else if (pid != 0)
	{
		wpid = waitpid(pid, &status, 0);
		g_exit_status = status >> 8;
	}
	return (0);
}

static int	free_buf(struct stat *buf, int result)
{
	free(buf);
	return (result);
}

int			exec_path_non_builtin(t_nonbuiltin *t_non, t_ae t_ae_data,
								t_cmd *cmd_list, int *fds)
{
	if ((t_non->env_path = get_env_value("PATH", t_ae_data.envp)) == NULL)
		return (free_buf(t_non->buf, 0));
	if ((t_non->paths = ft_split(t_non->env_path, ':')) == NULL)
		return (free_buf(t_non->buf, 0));
	while (t_non->paths[++(t_non->i)] != NULL)
	{
		if ((t_non->tmp = strjoin_path(t_non->paths[t_non->i],
						cmd_list->cmdline[0].cmd)) == 0)
			return (free_buf(t_non->buf, 0));
		if (cmd_list->cmdline[0].cmd[0] != '\0'
				&& stat(t_non->tmp, t_non->buf) == 0)
		{
			if (non_builtin_exec(cmd_list, t_ae_data, t_non->tmp, fds) == -1)
				return (free_buf(t_non->buf, 0));
			t_non->flag = 1;
			free(t_non->tmp);
			break ;
		}
		free(t_non->tmp);
	}
	t_non->i = -1;
	while (t_non->paths[++(t_non->i)] != NULL)
		free(t_non->paths[t_non->i]);
	free(t_non->paths);
	return (-1);
}

int			non_builtin(t_cmd *cmd_list, char *argv[], char **envp, int fds[])
{
	t_nonbuiltin	t_non;
	t_ae			t_ae_data;

	t_non.i = -1;
	t_non.flag = 0;
	t_ae_data.argv = argv;
	t_ae_data.envp = envp;
	if (!(t_non.buf = (struct stat*)malloc(sizeof(struct stat))))
		return (free_buf(t_non.buf, 0));
	if (cmd_list->cmdline[0].cmd[0] != '\0'
			&& stat(cmd_list->cmdline[0].cmd, t_non.buf) == 0)
	{
		if ((non_builtin_exec(cmd_list, t_ae_data,
						cmd_list->cmdline[0].cmd, fds)) == -1)
			return (free_buf(t_non.buf, 0));
		t_non.flag = 1;
	}
	else
	{
		if (exec_path_non_builtin(&t_non, t_ae_data, cmd_list, fds) == 0)
			return (0);
	}
	if (t_non.flag == 0)
		return (free_buf(t_non.buf, 0));
	return (free_buf(t_non.buf, 1));
}
